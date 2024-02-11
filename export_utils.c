/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:01 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/11 22:41:38 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	isvalid_export_input(char *str)
{
	char	**var_val;

	if (!str)
		return (0);
	if (!ft_strchr(str, '='))
		return (0);
	var_val = var_split(str, '=');
	if (!var_val)
		malloc_error();
	if (!isvalid_var_name_str(var_val[0]))
	{
		ft_free_arr(var_val);
		return (0);
	}
	ft_free_arr(var_val);
	return (1);
}

// valid var_name-> a-zA-Z0-9_
int	isvalid_var_name_str(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str) || *str == '=')
	{
		return (0);
	}
	while (str[i] != '=' && str[i])
	{
		if (!isvalid_var_name_char(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// valid var_name-> a-zA-Z0-9_
int	isvalid_var_name_char(int c)
{
	if (!ft_isalnum(c) && c != 95)
	{
		return (0);
	}
	return (1);
}

// return 0 - if no quotes, -1 - if qouts don't close, 1 = ', 2 = "
int	is_quotes(char *value)
{
	int	i;
	int	res;
	int	size;

	i = 0;
	res = 0;
	size = ft_strlen(value);
	while (i < size && value[i])
	{
		if (value[i] == 39)
		{
			i++;
			res = 1;
			while (value[i] != 39)
			{
				if (value[i] == '\0')
					return (-1);
				i++;
			}
		}
		else if (value[i] == 34)
		{
			i++;
			res = 2;
			while (value[i] != 34)
			{
				if (value[i] == '\0')
					return (-1);
				i++;
			}
		}
		i++;
	}
	return (res);
}
