/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:54:05 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/12 00:07:23 by ohladkov         ###   ########.fr       */
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
