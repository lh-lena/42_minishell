/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:14:32 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/11 12:12:50 by ohladkov         ###   ########.fr       */
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

void	put_error_arg(t_data *data, char *msg, char *arg, char *msg2, int er_n)
{
	data->exit_status = er_n;
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd(32, 2);
	ft_putendl_fd(msg2, 2);
}
