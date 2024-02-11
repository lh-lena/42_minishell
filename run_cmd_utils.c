/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:35:16 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/11 10:02:00 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*file_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (str[0] == str[1])
		i = 2;
	else
		i = 1;
	while (str[i] && is_whitespace(str[i]))
		i++;
	res = &str[i];
	return (res);
}

char	*get_delim(char *str)
{
	char	*res;
	int		i;

	i = 2;
	while (is_whitespace(str[i]))
		i++;
	res = &str[i];
	return (res);
}

void	open_pipes(t_data *data)
{
	int	**pp_fds;
	int	*p_fds;
	int	i;

	pp_fds = NULL;
	pp_fds = (int **)malloc(data->pipes_nb * sizeof(int *));
	if (!pp_fds)
		malloc_error();
	i = 0;
	while (i < data->pipes_nb)
	{
		p_fds = (int *)malloc(2 * sizeof(int));
		if (!p_fds)
			malloc_error();
		if (pipe(p_fds) == -1)
		{
			put_error(data, "Pipe open failed", errno);
			return ;
		}
		pp_fds[i] = p_fds;
		i++;
	}
	data->pipe_fds = pp_fds;
	// printf("pipe fds: %i, %i\n", data->pipe_fds[0][0], data->pipe_fds[0][1]); // delete
	return ;
}

void	close_pipes(t_data *data, int indx)
{
	(void)indx;
	int	**fds;
	int	i;
	int	j;

	if (!data->pipe_fds)
		return ;
	fds = data->pipe_fds;
	i = 0;
	while (i < data->pipes_nb)
	{
		j = 0;
		while (j < 2)
		{
			if (close(fds[i][j]) == -1)
				j++;
			else
				j++;
		}
		i++;
	}
	// while (i < data->pipes_nb)
	// {
	// 	j = 0;
	// 	while (j < 2)
	// 	{
	// 		if (indx == 0 && (i != indx && j != 1))
	// 			close(fds[i][j]);
	// 		else if (indx > 0)
	// 		{
	// 			if ((i != indx - 1 && j != 0) || (i != indx && j != 1))
	// 				close(fds[i][j]);
	// 		}
	// 		else if (indx == -1)
	// 			close(fds[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
}
