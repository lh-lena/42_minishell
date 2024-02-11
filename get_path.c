/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:30:07 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/11 22:39:47 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static size_t	str_len(char *str)
{
	size_t	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*ft_strcat(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!str1 && !str2)
		return (NULL);
	new_str = (char *)malloc(str_len(str1) + str_len(str2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str1 && str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
	{
		new_str[i + j] = str2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

static char	*find_str(char **src, char *str)
{
	char	*res;
	int		i;
	int		j;

	res = NULL;
	i = 0;
	j = 0;
	while (src[i])
	{
		while (src[i][j] == str[j])
			j++;
		if (str[j] == '\0')
			return (src[i]);
		i++;
	}
	return (res);
}

char	**get_path(char *envp[])
{
	char	**path;
	char	*str;
	int		i;

	str = find_str(envp, "PATH");
	if (!str)
		return (NULL);
	str = str + 5;
	if (!str)
		return (NULL);
	path = ft_split(str, ':');
	i = 0;
	while (path[i])
	{
		str = path[i];
		path[i] = ft_strcat(path[i], "/");
		free(str);
		i++;
	}
	return (path);
}

// void	ft_free(char **ptrs)
// {
// 	int	i;

// 	if (!ptrs)
// 		return ;
// 	i = 0;
// 	while (ptrs[i])
// 	{
// 		free(ptrs[i]);
// 		i++;
// 	}
// 	free(ptrs);
// }
