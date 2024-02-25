/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:17:58 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 12:05:43 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	if (str[i] == str[i + 1])
		i++;
	i++;
	while (is_whitespace(str[i]) && str[i] != '\0')
		i++;
	return (i);
}

int	next_quotes(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		i++;
	return (i);
}

int	find_next_del(char *str)
{
	int		i;

	i = 0;
	while (!is_whitespace(str[i]) && str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			i = i + next_quotes(&str[i], str[i]);
		else if (str[i] == '<' || str[i] == '>')
		{
			if (i == 0)
				i = i + skip_spaces(&str[i]);
			else
				return (i);
		}
		else if (str[i] == '|')
			return (i);
		else
			i++;
	}
	return (i);
}

void	add_cmd(t_command **lst, t_command *node)
{
	t_command	*cur;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

char	**create_arr_for(t_tocken *lst, char type)
{
	int			i;
	t_tocken	*cur;
	char		**res;

	cur = lst;
	i = 0;
	res = NULL;
	while (cur && !is_pipe(cur))
	{
		if (type == 'r' && is_redir(cur))
			i++;
		else if (type == 'c' && !is_redir(cur))
			i++;
		cur = cur->next;
	}
	if (i == 0)
		return (NULL);
	res = (char **)malloc((i + 1) * sizeof(char *));
	if (!res)
		return (malloc_error());
	return (res);
}
