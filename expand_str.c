/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:53 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/22 15:33:47 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// return pointer to new allocated string without qoutes, replaced variable
char	*expand_str(t_data *data, char *input)
{
	char	*temp_new;

	temp_new = NULL;
	if (is_quotes(input) || ft_strchr(input, '$') || ft_strchr(input, '\\'))
	{
		temp_new = substitute_str(data, input);
		if (!temp_new)
			malloc_error();
	}
	else
	{
		temp_new = ft_strdup(input);
		if (!temp_new)
			malloc_error();
	}
	return (temp_new);
}
