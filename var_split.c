/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:22 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 13:41:23 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**var_split(char *s, char c)
{
	char			**res;
	unsigned int	i;

	res = (char **)ft_calloc(2 + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
		i++;
	res[0] = ft_substr(s, 0, i);
	if (res[0] == NULL)
		return (res);
	res[1] = ft_substr(s, i + 1, ft_strlen(s) - i - 1);
	if (res[1] == NULL)
		return (res);
	res[2] = NULL;
	return (res);
}
