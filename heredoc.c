/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:42:14 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/11 22:33:58 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//void	read_heredoc(t_data *data, char *delim, int fd);
static char	*edit_str_hd(t_data *data, char *str);

// void	heredoc(t_data *data, char *delim)
// {
// 	int	fd;

// 	fd = open(data->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0777);
// 	read_heredoc(data, delim, fd);
// 	close(fd);
// }

void	read_heredoc(t_data *data, char *delim, int fd)
{
	char	*input;

	input = NULL;
	signal(SIGINT, new_line_h);
	while (1)
	{
		// rl_catch_signals = 0;
		input = readline("> ");
		// printf("g_sig_status : %d\n", g_sig_status);
		if (g_sig_status == 1)
		{
			g_sig_status = 0;
			return ;
		}
		if (!input)
		{
			printf("bash: warning: here-document delimited by end-of-file\
(wanted `%s')\n", delim);
			return ;
		}
		// if (*data->input == '\0')
		// 	ft_putstr_fd("", 1);
		// else if (is_whitespace_str(data->input))
		// 	ft_putstr_fd("", 1);
		if (ft_strncmp(input, delim, ft_strlen(input)) == 0)
			break ;
		input = edit_str_hd(data, input);
		ft_putendl_fd(input, fd);
		ft_free(&input);
	}
	// signal(SIGINT, SIG_DFL);
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
