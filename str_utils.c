/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:54:05 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/06 22:56:14 by ohladkov         ###   ########.fr       */
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


