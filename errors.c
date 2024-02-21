/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:14:32 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/19 13:08:38 by ohladkov         ###   ########.fr       */
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
