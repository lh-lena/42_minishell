/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:54:05 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/17 16:25:26 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	ft_isdigit_str(char *s)
{
	int	j;

	j = 0;
	if (ft_issign(s[j]))
	{
		j++;
		while (s[j])
		{
			if (ft_isdigit(s[j]) == 0)
				return (0);
			j++;
		}
	}
	else
	{
		while (s[j])
		{
			if (ft_isdigit(s[j]) == 0)
				return (0);
			j++;
		}
	}
	return (1);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_issign(int c)
{
	if (c == 43 || c == 45)
		return (1);
	return (0);
}

int	is_whitespace_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	str_copy(char *s1, char *s2)
{
	if (!s2 || *s2 == '\0')
		return ;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
}

int	isspecial_char(int c)
{
	return (c == 34 || c == 36 || c == 92 || c == 96);
}

int	handle_name(int	c)
{
	return (c == '?');
}

int is_ctrl_c(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)3)
			return (1);
		i++;
	}
	return (0);
}
