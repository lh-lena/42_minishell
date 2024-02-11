/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdzhoha <kdzhoha@student.42berlin.de >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:17:58 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/01/26 17:27:59 by kdzhoha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

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

int	find_next_del(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (!is_whitespace(str[i]) && str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] != '\0')
				i++;
		}
		else if (str[i] == '<' || str[i] == '>')
			i = i + skip_spaces(&str[i]);
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
