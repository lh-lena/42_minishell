/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:01 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/22 15:32:58 by ohladkov         ###   ########.fr       */
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

// return 0 - if no quotes, -1 - if qouts don't close, 39 = ', 34 = "
int	is_quotes(char *value)
{
	int		res;
	int		i;
	char	c;

	res = 0;
	i = -1;
	c = 0;
	while (value[++i] != '\0')
	{
		if (value[i] == 39 || value[i] == 34)
		{
			c = value[i];
			i++;
			while (value[i] != c && value[i])
				i++;
			if (value[i] == c)
				res = c;
			else
				return (-1);
		}
	}
	return (res);
}
