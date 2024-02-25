/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:36:40 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/25 16:39:45 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_calc_exit_status(char *str);
static int	check_exit_arg(t_data *data, char *str);

int	is_exit(t_data *data, char **arr)
{
	int		size;
	int		i;

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
		if (data->pipes_nb == 0)
			ft_putendl_fd("exit", 2);
		ft_putstr_fd("bash: exit: ", 2);
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
	rl_clear_history();
	if (data)
		ft_free_on_exit(data);
	ft_putendl_fd("exit", 2);
	exit(num);
}

size_t	exit_len(t_data *data)
{
	size_t	len;

	data->exit_c = ft_itoa(data->exit_status);
	len = ft_strlen(data->exit_c);
	ft_free(&data->exit_c);
	return (len);
}
