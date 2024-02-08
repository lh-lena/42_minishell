/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:24:02 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/08 17:18:09 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_echo_n(char *str);
static void	echo_print(t_data *data, char **arr);

void	echo_builtin(t_data *data, char **arr)
{
	size_t 	i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (++i < ft_arrsize(arr))
	{
		temp = arr[i];
		arr[i] = expand_str(data, temp);
		if (!arr[i])
			malloc_error();
		ft_free(&temp);
	}
	echo_print(data, arr);
	// data->exit_status = 0;
}

static void	echo_print(t_data *data, char **arr)
{
	size_t	i;
	size_t	size;
	int		n;

	(void)data;
	i = 0;
	n = 0;
	size = ft_arrsize(arr);
	while (++i < size)
	{
		if (check_echo_n(arr[i]))
			n = 1;
		else
		{
			ft_putstr_fd(arr[i], 1);
			if (i != size - 1)
				ft_putchar_fd(' ', 1);
		}
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("", 1);
	// printf("exit_status: %d\n", data->exit_status);
}

static int	check_echo_n(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 2;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
