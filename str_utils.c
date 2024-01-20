/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:54:05 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/19 20:28:05 by ohladkov         ###   ########.fr       */
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
	str = (char *)ft_calloc((len + 1),sizeof(char));
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
