/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:36:19 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 13:36:23 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_error(t_data *data, char *msg,  int er_num)
{
	data->exit_status = er_num;
	ft_putendl_fd(msg, 2);
}

void	print_error_arg(t_data *data, char *msg, char *arg, char *msg2, int er_num)
{
	data->exit_status = er_num;
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg2, 2);
}
