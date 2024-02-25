/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdzhoha <kdzhoha@student.42berlin.de >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:14:32 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/20 14:30:06 by kdzhoha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	*malloc_error(void)
{
	printf("Malloc error");
	return (NULL);
}

void	put_error(t_data *data, char *msg, int er_num)
{
	data->exit_status = er_num;
	ft_putendl_fd(msg, 2);
}

void	*put_error_free(t_data *data, char *msg, int er_num)
{
	put_error(data, msg, er_num);
	ft_free_data(data);
	return (NULL);
}
