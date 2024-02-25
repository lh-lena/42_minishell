/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:58:58 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 18:09:11 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	get_input_fd(char **redir, int p_fd, t_data *data)
{
	int	fd;
	int	i;

	fd = p_fd;
	i = 0;
	while (redir && redir[i])
	{
		if (redir[i][0] == '<')
		{
			if (fd > 0)
				close(fd);
			fd = input_fd(redir[i], data);
			if (fd == -2)
				return (-2);
		}
		i++;
	}
	return (fd);
}

int	get_output_fd(char **redir, int p_fd, t_data *data)
{
	int	fd;
	int	i;

	fd = p_fd;
	i = 0;
	while (redir && redir[i])
	{
		if (redir[i][0] == '>')
		{
			if (fd > 0)
				close(fd);
			if (*(file_name(redir[i])) == '\0')
			{
				put_error(data, "bash: ambiguous redirect", 1);
				return (-2);
			}
			fd = output_fd(redir[i], data);
			if (fd == -2)
				return (-2);
		}
		i++;
	}
	return (fd);
}

void	run_command(t_command *cmd, pid_t *pr_id, t_data *data, int i)
{
	int	fd_in;
	int	fd_out;
	int	error;

	fd_in = -1;
	fd_out = -1;
	error = 0;
	if (i > 0)
		fd_in = data->pipe_fds[i - 1][0];
	fd_in = get_input_fd(cmd->redir, fd_in, data);
	if (fd_in == -2)
		error = -1;
	ft_dup2(fd_in, STDIN_FILENO);
	if (data->pipes_nb > i)
		fd_out = data->pipe_fds[i][1];
	if (error == 0)
		fd_out = get_output_fd(cmd->redir, fd_out, data);
	if (fd_out == -2)
		error = -1;
	ft_dup2(fd_out, STDOUT_FILENO);
	if (check_check(data, pr_id, cmd->cmd, error) == -1)
		return ;
	ft_fork(data, cmd->cmd, pr_id);
}

void	ft_wait(t_data *data, int status, int j)
{
	int	i;

	i = 0;
	while (i < data->cmd_nb)
	{
		if (data->pr_id[i] > 0)
			waitpid(data->pr_id[i], &status, 0);
		if (status >= 0)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if ((WTERMSIG(status) == 2 || WTERMSIG(status) == 3) && j == 0)
				{
					data->exit_status = 128 + WTERMSIG(status);
					j = 1;
					write(1, "\n", 1);
				}
				g_sig_status = 0;
			}
		}
		i++;
	}
}

void	process_command(t_data *data)
{
	t_command	*cur;
	int			i;

	i = 0;
	if (data->pipes_nb)
		open_pipes(data);
	cur = data->cmd;
	data->pr_id = (int *)malloc(data->cmd_nb * sizeof(int));
	while (cur)
	{
		run_command(cur, &data->pr_id[i], data, i);
		cur = cur->next;
		i++;
	}
	close_pipes_free(data);
	ft_wait(data, -1, 0);
	if (data->pr_id)
	{
		free(data->pr_id);
		data->pr_id = NULL;
	}
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
}
