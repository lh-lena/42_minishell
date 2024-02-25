/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdzhoha <kdzhoha@student.42berlin.de >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:24 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/23 17:10:18 by kdzhoha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_free_on_exit(t_data *data)
{
	if (!data)
		return ;
	if (data->env_lst)
		ft_free_lst_env(data->env_lst);
	ft_free_data(data);
	free(data);
}

void	free_cmd_pipes(t_data *data)
{
	free_command_lst(data->cmd);
	data->cmd = NULL;
	data->cmd_nb = 0;
	data->pipe_fds = NULL;
	data->pipes_nb = 0;
	data->pr_id = NULL;
}

void	ft_free_data(t_data	*data)
{
	if (data->new_envp)
	{
		ft_free_arr(data->new_envp);
		data->new_envp = NULL;
	}
	if (data->cmd)
	{
		free_command_lst(data->cmd);
		data->cmd = NULL;
	}
	if (data->pipes_nb)
	{
		close_pipes(data);
		free_array(data->pipe_fds, data->pipes_nb);
		data->pipe_fds = NULL;
		data->pipes_nb = 0;
	}
	if (data->input)
		ft_free(&data->input);
	if (data->pr_id)
	{
		free(data->pr_id);
		data->pr_id = NULL;
	}
}

void	ft_free_arr(char **arr)
{
	char	**temp;
	int		i;

	i = 0;
	if (arr != NULL)
	{
		temp = arr;
		while (temp[i])
		{
			if (temp[i])
			{
				ft_free(&temp[i]);
			}
			i++;
		}
		free(temp);
		temp = NULL;
	}
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
