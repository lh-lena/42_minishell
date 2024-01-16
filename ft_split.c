/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:34:10 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/16 12:15:01 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// static unsigned int	ft_words(char const *s, char c)
// {
// 	unsigned int	nb;

// 	nb = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 			nb++;
// 		while (*s && *s != c)
// 			s++;
// 		while (*s && *s == c)
// 			s++;
// 	}
// 	return (nb);
// }

// static char	*ft_wordalloc(char const *s, char c)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	len;

// 	i = 0;
// 	while ((char)s[i] && (char)s[i] != c)
// 		i++;
// 	len = i;
// 	// str = (char *)malloc(sizeof(char) * (len + 1));
// 	str = (char *)ft_calloc(len + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = (char)s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char			**str_new;
// 	unsigned int	num_words;
// 	size_t			i;

// 	num_words = ft_words(s, c);
// 	str_new = (char **)malloc(sizeof(char *) * (num_words + 1));
// 	if (!str_new)
// 		return (NULL);
// 	i = 0;
// 	while (i < num_words)
// 	{
// 		while (*s == c && *s)
// 			s++;
// 		if (*s != c && *s)
// 		{
// 			str_new[i] = ft_wordalloc(s, c);
// 			if (!str_new[i])
// 				return (str_new);
// 		}
// 		while (*s != c && *s)
// 			s++;
// 		i++;
// 	}
// 	str_new[i] = NULL;
// 	return (str_new);
// }

static char	*ft_strcpy(char const *str, char end)
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	while ((char)str[i] != end && (char)str[i] != '\0')
		i++;
	len = i;
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (res);
	i = 0;
	while (i < len)
	{
		res[i] = (char)str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static unsigned int	ft_count_words(char const *str, char c)
{
	unsigned int	nb;
	char			*s;

	s = (char *)str;
	nb = 0;
	while (*s != '\0')
	{
		if (*s != c)
			nb++;
		while (*s != c && *s != '\0')
			s++;
		while (*s == c && *s != '\0')
			s++;
	}
	return (nb);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	i;
	unsigned int	n;

	n = ft_count_words(s, c);
	res = (char **)ft_calloc(n + 1, sizeof(char *));
	if (res == NULL)
		return (res);
	i = 0;
	while (i < n)
	{
		while ((char)*s == c && *s != '\0')
			s++;
		if ((char)*s != c)
		{
			res[i] = ft_strcpy(s, c);
			if (res[i] == NULL)
				return (res);
		}
		while ((char)*s != c && *s != '\0')
			s++;
		i++;
	}
	res[i] = NULL;
	return (res);
}
