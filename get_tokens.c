/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:35:18 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 16:05:16 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tocken	*create_new(char *str)
{
	int			i;
	t_tocken	*new;

	i = 0;
	new = new_tocken();
	if (!new)
		return (NULL);
	new->begin = &str[i];
	if (str[i] == '|')
		i++;
	else
		i = i + find_next_del(&str[i]);
	new->end = (&str[i]);
	return (new);
}

void	add_to_res(t_tocken **res, t_tocken *new)
{
	t_tocken	*cur;

	if (!*res)
		*res = new;
	else
	{
		cur = *res;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

t_tocken	*get_tockens(char *str)
{
	t_tocken	*res;
	t_tocken	*new;
	int			i;

	res = NULL;
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			i++;
		else
		{
			new = new_tocken();
			new->begin = &str[i];
			if (str[i] == '|')
				i++;
			else
				i = i + find_next_del(&str[i]);
			new->end = (&str[i]);
			add_to_res(&res, new);
		}
	}
	return (res);
}
