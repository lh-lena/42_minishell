/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:32 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 13:35:35 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%d = %s\n", i, arr[i]);
		i++;
	}
}

size_t	ft_arrsize(char	**arr)
{
	size_t	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}
size_t	ft_arrlen(char **arr)
{
	size_t	size;
	int		i;

	i = -1;
	size = 0;
	while (arr[++i])
	{
		size += ft_strlen(arr[i]);
	}
	return (size);
}
