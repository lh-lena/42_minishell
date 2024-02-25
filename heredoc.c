/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:42:14 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/25 17:20:42 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*edit_str_hd(t_data *data, char *str);

int	write_heredoc(t_data *data, char *str)
{
	int		fd;

	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	fd = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	data->exit_status = 0;
	read_heredoc(data, str, fd);
	if (g_sig_status == 1)
	{
		g_sig_status = 0;
		if (close(fd) != -1)
			unlink(".heredoc");
		return (-1);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}

void	read_heredoc(t_data *data, char *delim, int fd)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if (g_sig_status == 1)
		{
			data->exit_status = 130;
			return ;
		}
		input = readline("> ");
		if (!input)
		{
			printf("bash: warning: here-document delimited by end-of-file\
(wanted `%s')\n", delim);
			return ;
		}
		if (ft_strncmp(input, delim, ft_strlen(input)) == 0)
			break ;
		input = edit_str_hd(data, input);
		ft_putendl_fd(input, fd);
		ft_free(&input);
	}
	if (input)
		free(input);
}

static char	*edit_str_hd(t_data *data, char *str)
{
	char	*temp;

	temp = NULL;
	if (ft_strchr(str, '$'))
	{
		temp = str;
		str = get_replaced_str(data, temp);
		free(temp);
	}
	return (str);
}
