/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:01 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/14 13:47:32 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	count_qoutes(char **str, int c);

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
int is_quotes(char *value)
{
	int		res;
	char	*temp;

	res = 0;
	temp = value;
	while (*temp)
	{
		if (*temp == 39)
		{
			res = count_qoutes(&temp, 39);
		}
		else if (*temp == 34)
		{
			res = count_qoutes(&temp, 34);
		}
		temp++;
	}
	return (res);
}

static int	count_qoutes(char **str, int c)
{
	int	res;

	if (c == 39)
		res = 1;
	else if (c == 34)
		res = 2;
	*str = *str + 1;
	while (**str != c)
	{
		if (**str == '\0')
			return (-1);
		*str = *str + 1;
	}
	return (res);
}
