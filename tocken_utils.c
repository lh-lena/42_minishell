/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:35:18 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/08 18:51:54 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tocken	*new_tocken(void)
{
	t_tocken	*new;

	new = (t_tocken *)malloc(sizeof(t_tocken));
	if (!new)
		return (malloc_error());
	new->begin = NULL;
	new->end = NULL;
	new->next = NULL;
	return (new);
}

t_tocken	*get_tockens(char *str)
{
	t_tocken	*res;
	t_tocken	*cur;
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
			// write (1, new->begin, 2);
			// write (1, "\n", 1);
			if (!res)
			{
				res = new;
				cur = new;
			}
			else
			{
				cur->next = new;
				cur = cur->next;
			}
		}
	}
	return (res);
}

int	is_pipe(t_tocken *tkn)
{
	int		i;
	char	*str;

	str = tkn->begin;
	i = 0;
	if (str[i] == '|')
		return (1);
	return (0);
}

int	is_redir(t_tocken *tkn)
{
	int		i;
	char	*str;

	str = tkn->begin;
	i = 0;
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

void	free_tockns_lst(t_tocken *lst)
{
	t_tocken	*cur;
	t_tocken	*temp;

	cur = lst;
	while (cur)
	{
		temp = cur->next;
		free(cur);
		cur = temp;
	}
}
