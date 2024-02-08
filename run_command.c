/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:58:58 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/08 18:43:19 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// Work in progress:
static void	write_heredoc(t_data *data, char *str)
{
	//(void)data;
	int		fd;

	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	fd = open(".heredoc",  O_WRONLY | O_TRUNC | O_CREAT, 0777);
	//write(fd, str, ft_strlen(str));
	read_heredoc(data, str, fd);
	close(fd);
	//return ;
}

// void	set_input_fd(int fd)
// {
// 	if (fd > 0)
// 	{
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
// 			put_error(data, "Invalid file descriptor", errno);
// 			return ;
// 		}
// 		close(fd);
// 	}
// }

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
				write_heredoc(data, get_delim(redir[i]));
				fd = open(".heredoc", O_RDONLY);
			}
			else
			{
				fd = open(file_name(redir[i]), O_RDONLY);
				if (fd < 0)
				{
					put_error(data, "File not found", errno);
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

// void	set_output_fd(int fd);
// {
// 	if (fd > 0)
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }

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
				fd = open(file_name(redir[i]), O_WRONLY | O_APPEND | O_CREAT, 0777);
				if (fd < 0)
				{
					put_error(data, "Invalid file name", errno);
					return ;
				}		
			}
			else
			{
				fd = open(file_name(redir[i]), O_WRONLY | O_TRUNC | O_CREAT, 0777);
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
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	if (i > 0)
		fd_in = data->pipe_fds[i - 1][0];
	set_input_fd(cmd->redir, fd_in, data);
	if (data->pipes_nb > i)
		fd_out = data->pipe_fds[i][1];
	set_output_fd(cmd->redir, fd_out, data);
	*pr_id = fork();
	if (*pr_id == 0)
	{
		close_pipes(data, -1);
		if (cmd->cmd)
			execve_tr(data, cmd->cmd);
		//check_cmd(data, cmd->cmd);
		exit(0);
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

	i = 0;
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
	status = -1;
	while (i < data->cmd_nb)
	{
		if (errno == ECHILD)
			printf("errno == ECHILD\n");
		// printf("Parent process: My PID is %d\n", getpid());
		if (waitpid(pr_id[i], &status, 0) == -1)
			perror("waitpid");
		// printf("WEXITSTATUS(status): %d\n", exit_code);
		// printf("status: %d\n", status);
		// printf("WIFEXITED(status): %d\n", WIFEXITED(status));
		// printf("WIFSIGNALED(status): %d\n", WIFSIGNALED(status));
		if (WIFEXITED(status))
		{
			data->exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			// printf("WTERMSIG(status): %d\n", WTERMSIG(status));
			data->exit_status = 130;
		}
		else
			data->exit_status = 0;
		i++;
	}
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	//return ;
}

// void	run_command(t_command *cmd, pid_t *pr_id, t_data *data, int i)
// {
// 	int		fd_in;
// 	int		fd_out;

// 	fd_in = -1;
// 	fd_out = -1;
// 	*pr_id = fork();
// 	if (*pr_id == 0)
// 	{
// 		if (i > 0)
// 			fd_in = data->pipe_fds[i - 1][0];
// 		set_input_fd(cmd->redir, fd_in, data);
// 		if (data->pipes_nb > i)
// 			fd_out = data->pipe_fds[i][1];
// 		set_output_fd(cmd->redir, fd_out, data);
// 		close_pipes(data, -1);
// 		if (cmd->cmd)
// 			execve_tr(data, cmd->cmd);
// 		//check_cmd(data, cmd->cmd);
// 		exit(0);
// 	}
// 	else
// 		return ;
// }
