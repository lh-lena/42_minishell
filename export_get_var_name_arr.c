/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_var_name_arr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:16 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 13:37:17 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static unsigned int	ft_words(char *s, char c)
{
	unsigned int	nb;

	nb = 0;
	while (*s)
	{
		if (*s == c && isvalid_var_name_char(*(s + 1)))
			nb++;
		s++;
	}
	return (nb);
}

static char	*ft_wordalloc(char *s, char c)
{
	char	*str;
	size_t	i;
	size_t	len;

	(void)c;
	i = 0;
	while (isvalid_var_name_char(s[i]))
		i++;
	len = i;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// return poiner to array of allocated VAR's name from the given string
char	**get_var_name_arr(char *s, char c)
{
	char			**arr;
	unsigned int	num_words;
	size_t			i;

	num_words = ft_words(s, c);
	arr = (char **)ft_calloc(num_words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		while (*s != c && *s)
			s++;
		if (*s == c && *s)
		{
			s++;
			arr[i] = ft_wordalloc(s, c);
			if (!arr[i])
				return (arr);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
