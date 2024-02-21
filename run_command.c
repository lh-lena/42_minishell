/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:58:58 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/21 16:52:30 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	write_heredoc(t_data *data, char *str)
{
	int		fd;

	if (!str)
	{
		put_error(data, "bash: syntax error near unexpected token `newline'", 2);
		return (-1); // added
	}
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	fd = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	read_heredoc(data, str, fd);
	if (g_sig_status == 1)
	{
		if (close(fd) != -1)
			unlink(".heredoc");
		return (-1);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}

void	set_input_fd(char **redir, int p_fd, t_data *data)
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
			if (redir[i][1] == '<')
			{
				if (write_heredoc(data, get_delim(redir[i])) != 0)
					fd = -1;
				else
					fd = open(".heredoc", O_RDONLY);
			}
			else
			{
				fd = open(file_name(redir[i]), O_RDONLY);
				if (fd < 0)
				{
					// put_error(data, "File not found", errno);
					put_error(data, "bash: No such file or directory", errno);
					return ;
				}
			}
		}
		i++;
	}
	if (fd > 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			put_error(data, "Invalid file descriptor", errno);
			return ;
		}
		close(fd);
	}
}

void	set_output_fd(char **redir, int p_fd, t_data *data)
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
			if (redir[i][1] == '>')
			{
				// printf("1set_output_fd; %s\n", redir[i]); // delete
				fd = open(file_name(redir[i]), O_WRONLY | O_APPEND | O_CREAT, 0777);
				// printf("2set_output_fd; %s\n", redir[i]); // delete
				if (fd < 0)
				{
					put_error(data, "Invalid file name", errno);
					return ;
				}
			}
			else
			{
				// printf("3set_output_fd; %s\n", redir[i]); // delete
				fd = open(file_name(redir[i]), O_WRONLY | O_TRUNC | O_CREAT, 0777);
				// printf("4set_output_fd; %s\n", redir[i]); // delete
				if (fd < 0)
				{
					put_error(data, "Invalid file name", errno);
					return ;
				}
			}
		}
		i++;
	}
	if (fd > 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	restore_fds(t_data *data)
{
	if (isatty(STDIN_FILENO) != 1)
		dup2(data->fd_inp, STDIN_FILENO);
	if (isatty(STDOUT_FILENO) != 1)
		dup2(data->fd_outp, STDOUT_FILENO);
	else
		return ;
}

void	run_command(t_command *cmd, pid_t *pr_id, t_data *data, int i)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	if (i > 0)
		fd_in = data->pipe_fds[i - 1][0];
	set_input_fd(cmd->redir, fd_in, data);
	if (data->pipes_nb > i)
		fd_out = data->pipe_fds[i][1];
	set_output_fd(cmd->redir, fd_out, data);
	if (cmd->cmd == NULL || g_sig_status == 1)
	{
		g_sig_status = 0; // added
		*pr_id = 0;
		restore_fds(data);
		return ;
	}
	signal_ignr();
	*pr_id = fork();
	if (*pr_id == 0)
	{
		manage_signal();
		close_pipes(data, -1);
		if (cmd->cmd)
			execve_tr(data, cmd->cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		restore_fds(data);
		return ;
	}
}

void	process_command(t_data *data)
{
	pid_t		pr_id[data->cmd_nb];
	t_command	*cur;
	int			i;
	int			status;
	int			j;

	i = 0;
	j = 0;
	status = -1;
	if (data->pipes_nb)
		open_pipes(data);
	cur = data->cmd;
	while (cur)
	{
		run_command(cur, &pr_id[i], data, i);
		cur = cur->next;
		i++;
	}
	close_pipes(data, -1);
	free_array(data->pipe_fds, data->pipes_nb);
	i = 0;
	while (i < data->cmd_nb)
	{
		if (pr_id[i] > 0)
			waitpid(pr_id[i], &status, 0);
		// printf("%d\n", status);
		// if (status < 0)
		// 	break ;
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			data->exit_status = 128 + WTERMSIG(status);
			if ((WTERMSIG(status) == 2 || WTERMSIG(status) == 3) && j == 0)
			{
				j = 1;
				write(1, "\n", 1);
			}
			g_sig_status = 0;
		}
		i++;
	}
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
}
