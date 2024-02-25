/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdzhoha <kdzhoha@student.42berlin.de >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:26:28 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/22 16:14:02 by kdzhoha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	count_pipes(t_command *lst)
{
	int			res;
	t_command	*cur;

	if (!lst)
		return (0);
	res = 0;
	cur = lst;
	while (cur->next)
	{
		res++;
		cur = cur->next;
	}
	return (res);
}

void	free_array(int **arr, int size)
{
	int	i;

	if (!arr || size == 0)
		return ;
	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_command_lst(t_command *cmd)
{
	t_command	*cur;
	t_command	*temp;

	cur = cmd;
	while (cur)
	{
		temp = cur->next;
		ft_free_arr(cur->cmd);
		ft_free_arr(cur->redir);
		free(cur);
		cur = temp;
	}
	cmd = NULL;
}
