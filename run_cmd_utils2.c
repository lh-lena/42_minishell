/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:35:16 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 17:32:27 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	check_check(t_data *data, pid_t *pr_id, char **cmd, int error)
{
	if (cmd == NULL || error == -1)
	{
		*pr_id = 0;
		restore_fds(data);
		return (-1);
	}
	if (g_sig_status == 1)
	{
		g_sig_status = 0;
		*pr_id = 0;
		restore_fds(data);
		return (-1);
	}
	return (0);
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

int	ft_dup2(int fd, int st_fd)
{
	if (fd < 0)
		return (-1);
	if (dup2(fd, st_fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	output_fd(char *redir, t_data *data)
{
	int	fd;

	if (redir[1] == '>')
	{
		fd = open(file_name(redir), O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd < 0)
		{
			write(2, file_name(redir), ft_strlen(file_name(redir)));
			put_error(data, ": No such file or directory", 1);
			return (-2);
		}
	}
	else
	{
		fd = open(file_name(redir), O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd < 0)
		{
			write(2, file_name(redir), ft_strlen(file_name(redir)));
			put_error(data, ": No such file or directory", 1);
			return (-2);
		}
	}
	return (fd);
}

int	input_fd(char *redir, t_data *data)
{
	int	fd;

	if (redir[1] == '<')
	{
		if (write_heredoc(data, get_delim(redir)) != 0)
			return (-2);
		else
			fd = open(".heredoc", O_RDONLY);
	}
	else
	{
		if (*(file_name(redir)) == '\0')
		{
			put_error(data, "bash: ambiguous redirect", 1);
			return (-2);
		}
		fd = open(file_name(redir), O_RDONLY);
		if (fd < 0)
		{
			put_error(data, "bash: No such file or directory", 1);
			return (-2);
		}
	}
	return (fd);
}
