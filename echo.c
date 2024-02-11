/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:24:02 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/11 22:36:18 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_echo_n(char *str);

void	echo_builtin(t_data *data, char **arr)
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
