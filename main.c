/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:06:19 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/20 16:42:53 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int g_sig_status = 0;

void	print_result(t_command *cmd)
{
	int		i;

	while (cmd != NULL)
	{
		i = 0;
		while (cmd->cmd && cmd->cmd[i])
		{
			printf("cmd%i: %s\n", i, cmd->cmd[i]);
			i++;
		}
		i = 0;
		while (cmd->redir && cmd->redir[i])
		{
			printf("redir%i: %s\n", i, cmd->redir[i]);
			i++;
		}
		cmd = cmd->next;
	}
}

void	execve_tr(t_data *data, char **arr)
{
	char	*temp;
	int		val;

	if (!arr[0])
		return ;
	val = 0;
	temp = arr[0];
	if (ft_strncmp(temp, "pwd", ft_strlen(temp)) == 0)
		pwd_cmd(data);
	else if (ft_strncmp(temp, "echo", ft_strlen(temp)) == 0)
		echo_builtin(data, arr);
	else if (ft_strncmp(temp, "env", ft_strlen(temp)) == 0)
		env_print(data);
	else
		val = execute(arr, data->new_envp);
	if (val == -1)
	{
		printf("%s: command not found\n", arr[0]);
		exit(127);
	}
}

// removed all builtins that could be run within pipes, moved them to execve_tr
int	check_cmd(t_data *data, char **arr)
{
	int		res;
	char	*temp;

	if (!arr || data->pipes_nb != 0 || !*arr) // added !*arr
		return (0);
	res = 1;
	temp = arr[0];
	if (ft_strncmp(temp, "exit", ft_strlen(temp)) == 0)
	{
		if (is_exit(data))
			exit_handler(data);
	}
	else if (ft_strncmp(temp, "export", ft_strlen(temp)) == 0)
		export(data, arr);
	else if (ft_strncmp(temp, "unset", ft_strlen(temp)) == 0)
		unset(data, arr);
	else if (ft_strncmp(temp, "cd", ft_strlen(temp)) == 0)
		cd_builtin(data, arr);
	else
		return (0);
	return (res);
}

int	alloc_expand(char **arr, t_data *data)
{
	int		size;
	int		i;
	char	*tmp;
	char	**temp;

	size = 0;
	i = 0;
	tmp = NULL;
	temp = arr;
	while (arr[i])
	{
		if (is_quotes(temp[i]) == 0 && ft_strchr(temp[i], '$'))
		{
			tmp = get_replaced_str(data, temp[i]);
			printf("tmp: %s\n", tmp);
			size += ft_count_words(tmp, 32);
			ft_free(&tmp);
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	**expand_arr(char **arr, t_data *data)
{
	char	**res;
	char	*str;
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = alloc_expand(arr, data);
	printf("i = %d\n", i);
	res = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	j = 0;
	k = 0;
	str = NULL;
	temp = NULL;
	while (arr[i])
	{
		j = is_quotes(arr[i]);
		str = expand_str(data, arr[i]);
		printf("str: %s\n", str);
		if (j == 0 && ft_count_words(str, 32) > 1 && !is_redir_str(str))
		{
			temp = ft_split(str, 32);
			while (j < ft_count_words(str, 32))
			{
				res[k] = ft_strdup(temp[j]);
				k++;
				j++;
			}
			ft_free_arr(temp);
		}
		else if (ft_count_words(str, 32) > 1 && is_redir_str(str))
		{
			printf("bash: %s: ambiguous redirect\n", ft_strchr(arr[i], 36));
			return (NULL);
		}
		else
		{
			res[k] = ft_strdup(str);
			k++;
		}
		ft_free(&str);
		i++;
	}
	res[k] = NULL;
	return (res);
}

void	expand_input(t_data *data)
{
	char		**temp;
	t_command	*cur;

	cur = data->cmd;
	while (cur)
	{
		if (cur->cmd)
		{
			temp = cur->cmd;
			cur->cmd = expand_arr(temp, data);
			ft_free_arr(temp);
		}
		if (cur->redir)
		{
			temp = cur->redir;
			cur->redir = expand_arr(temp, data);
			ft_free_arr(temp);
		}
		cur = cur->next;
	}
}

static void	init_data(t_data *data)
{
	data->exit_status = 0;
	data->cmd = NULL;
	data->len = 0;
	data->new_envp = NULL;
	data->exit_c = NULL;
	data->pipes_nb = 0;
	data->cmd_nb = 0;
	data->fd_inp = dup(STDIN_FILENO);
	data->fd_outp = dup(STDOUT_FILENO);
	data->pipe_fds = NULL;
}

void	minishell(t_data *data)
{
	t_command	*cmd;

	cmd = NULL;
	while (1)
	{
		data->input = readline("minishell$ ");
		if (g_sig_status == 1)
		{
			g_sig_status = 0;
			data->exit_status = 130;
			if (*data->input != '\0')
			{
				ft_putstr_fd("", 1);
				continue ;
			}
		}
		if (data->input == NULL)
			exit_handler(data);
		if (*data->input == '\0') 
			ft_putstr_fd("", 1);
		else if (is_whitespace_str(data->input))
		{
			create_history(data);
			ft_free(&data->input);
			ft_putstr_fd("", 1);
		}
		else if (is_quotes(data->input) == -1)
		{
			create_history(data);
			ft_free(&data->input);
			put_error(data, "bash: Quotes are not correctly closed", 5);
		}
		else
		{
			create_history(data);
			data->new_envp = new_envp(data);
			cmd = parse_input(data);
			data->cmd = cmd;
			expand_input(data);
			if (check_cmd(data, data->cmd->cmd) == 0)
				process_command(data);
			if (data->cmd)
			{
				free_command_lst(data->cmd);
				data->cmd = NULL;
				data->cmd_nb = 0;
				data->pipe_fds = NULL;
				data->pipes_nb = 0;
			}
			if (data->new_envp)
			{
				ft_free_arr(data->new_envp);
				data->new_envp = NULL;
			}
			signals();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;

	(void)argv;
	if (argc != 1)
		return (0);
	rl_catch_signals = 0;
	signals();
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		malloc_error();
	init_data(data);
	data->env_lst = ft_getenv(envp);
	minishell(data);
	return (0);
}
