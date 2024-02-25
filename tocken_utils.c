/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tocken_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:35:18 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 12:11:01 by ohladkov         ###   ########.fr       */
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

int	is_redir_str(char *str)
{
	return (str[0] == '<' || str[0] == '>');
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
