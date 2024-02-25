/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:06:19 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 16:26:58 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	g_sig_status = 0;

void	process_input(t_data *data)
{
	t_command	*cmd;

	cmd = NULL;
	create_history(data);
	data->new_envp = new_envp(data);
	cmd = parse_input(data);
	if (cmd)
	{
		data->cmd = cmd;
		expand_input(data);
		if (check_builtin(data, data->cmd->cmd) == 0)
			process_command(data);
	}
	if (data->cmd)
		free_cmd_pipes(data);
	if (data->new_envp)
	{
		ft_free_arr(data->new_envp);
		data->new_envp = NULL;
	}
	ft_free(&data->input);
	signals();
}

void	input_check(t_data *data)
{
	if (data->input == NULL)
		exit_handler(data);
	if (*data->input == '\0')
	{
		ft_free(&data->input);
		ft_putstr_fd("", 1);
	}
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
		process_input(data);
}

void	minishell(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell$ ");
		if (g_sig_status == 1)
		{
			g_sig_status = 0;
			data->exit_status = 130;
			if (*data->input != '\0')
			{
				ft_free(&data->input);
				ft_putstr_fd("", 1);
				continue ;
			}
		}
		input_check(data);
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
	data->pr_id = NULL;
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
