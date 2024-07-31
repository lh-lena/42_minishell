/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:53:45 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/29 10:39:20 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	execute(char **cmd, char *envp[])
{
	char	*path;
	char	**dir;
	int		res;
	int		i;
	int		j;

	j = 0;
	if (*cmd[j] == '\0' && cmd[j + 1])
		j++;
	else if (*cmd[j] == '\0')
		return (0);
	if (access(cmd[j], F_OK) == 0)
		return (execve(cmd[j], &cmd[j], envp));
	dir = get_path(envp);
	if (!dir)
		return (-1);
	i = -1;
	while (dir[++i])
	{
		path = ft_strcat(dir[i], cmd[j]);
		res = execve(path, &cmd[j], envp);
		free(path);
	}
	ft_free_arr(dir);
	return (res);
}

void	execve_tr(t_data *data, char **arr)
{
	int	val;

	if (!arr[0])
		return ;
	val = check_cmd(data, arr);
	if (val == 0)
		val = execute(arr, data->new_envp);
	if (val == -1)
	{
		write(2, arr[0], ft_strlen(arr[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

int	check_builtin(t_data *data, char **arr)
{
	int		res;
	char	*temp;

	if (!arr || data->pipes_nb != 0)
		return (0);
	res = 1;
	temp = arr[0];
	if (ft_strncmp(temp, "exit", ft_strlen(temp)) == 0)
	{
		if (is_exit(data, arr) && data->pipes_nb == 0)
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

int	check_cmd(t_data *data, char **arr)
{
	int		res;
	char	*temp;

	res = 1;
	temp = arr[0];
	if (ft_strncmp(temp, "exit", ft_strlen(temp)) == 0)
	{
		if (is_exit(data, arr)) // && data->pipes_nb == 0
			exit_handler(data);
	}
	else if (ft_strncmp(temp, "pwd", ft_strlen(temp)) == 0)
		pwd_cmd(data);
	else if (ft_strncmp(temp, "env", ft_strlen(temp)) == 0)
		env_print(data);
	else if (ft_strncmp(temp, "export", ft_strlen(temp)) == 0)
		export(data, arr);
	else if (ft_strncmp(temp, "unset", ft_strlen(temp)) == 0)
		unset(data, arr);
	else if (ft_strncmp(temp, "cd", ft_strlen(temp)) == 0)
		cd_builtin(data, arr);
	else if (ft_strncmp(arr[0], "echo", ft_strlen(arr[0])) == 0)
		echo_builtin(data, arr);
	else
		return (0);
	return (res);
}

void	ft_fork(t_data *data, char **cmd, pid_t *pr_id)
{
	signal_ignr();
	*pr_id = fork();
	if (*pr_id == 0)
	{
		manage_signal();
		close_pipes(data);
		if (cmd)
			execve_tr(data, cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		restore_fds(data);
		return ;
	}
}
