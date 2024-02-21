/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:36:40 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/21 11:34:26 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_calc_exit_status(char *str);
static int	check_exit_arg(t_data *data, char *str);

int	is_exit(t_data *data)
{
	char	**arr;
	int		size;
	int		i;

	arr = ft_split(data->input, ' ');
	if (!arr)
		malloc_error();
	size = ft_arrsize(arr);
	i = 1;
	if (size == 1)
		i = 1;
	else if (check_exit_arg(data, arr[1]) != 1 && size > 2)
	{
		i = 0;
		data->exit_status = 1;
		ft_putendl_fd("exit\nbash: exit: too many arguments", 2);
	}
	ft_free_arr(arr);
	return (i);
}

static int	check_exit_arg(t_data *data, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = expand_str(data, str);
	if (ft_isdigit_str(tmp))
		data->exit_status = ft_calc_exit_status(tmp);
	else
	{
		i = 1;
		data->exit_status = 2;
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	free(tmp);
	return (i);
}

static int	ft_calc_exit_status(char *str)
{
	int	code;

	code = ft_atoi(str) % 256;
	if (code < 0)
		code += 256;
	return (code);
}

void	exit_handler(t_data *data)
{
	int		num;

	num = data->exit_status;
	clear_history();
	if (data)
		ft_free_data(data);
	ft_putendl_fd("exit", 2);
	exit(num);
}
