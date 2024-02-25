/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:08:02 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/25 13:20:23 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

int	handle_name(int c)
{
	return (c == '?');
}

int	ft_count_words(char *str, char c)
{
	int		nb;
	char	*s;

	if (*str == '\0')
		return (1);
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

int	check_dir(char *path)
{
	DIR	*temp_dir;

	temp_dir = opendir(path);
	if (temp_dir)
	{
		if (closedir(temp_dir) == -1)
			perror("closedir");
		return (1);
	}
	else
		return (0);
}
