/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:13:07 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 17:26:28 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	get_offset(t_tocken *tkn, char *str, int size)
{
	int	ofset;

	ofset = 0;
	if (size < 2)
		return (-1);
	else if (size == 2 && is_whitespace(str[1]))
		return (-1);
	if (size > 2)
	{
		while (is_whitespace(str[ofset + 2]) && &str[ofset + 2] != tkn->end)
			ofset++;
	}
	return (ofset);
}

char	*copy_redir(t_tocken *tkn)
{
	int		i;
	int		ofset;
	int		size;
	char	*str;
	char	*res;

	res = NULL;
	str = tkn->begin;
	size = tkn->end - tkn->begin;
	ofset = get_offset(tkn, str, size);
	if (ofset == -1)
		return (NULL);
	res = (char *)malloc((size - ofset + 1) * sizeof(char));
	if (!res)
		return (malloc_error());
	res[0] = str[0];
	res[1] = str[1];
	i = 2;
	while ((&str[i + ofset] != tkn->end))
	{
		res[i] = str[i + ofset];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*copy_content(t_tocken *tkn)
{
	int		i;
	int		size;
	char	*str;
	char	*res;

	str = tkn->begin;
	size = tkn->end - tkn->begin;
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (malloc_error());
	i = 0;
	while (&str[i] != tkn->end)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**get_command(t_tocken *lst)
{
	int			i;
	t_tocken	*cur;
	char		**cmd;

	cur = lst;
	cmd = create_arr_for(lst, 'c');
	if (!cmd)
		return (NULL);
	i = 0;
	while (cur && !is_pipe(cur))
	{
		if (!is_redir(cur))
		{
			cmd[i] = copy_content(cur);
			i++;
		}
		cur = cur->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**get_redir(t_tocken *lst)
{
	char		**redir;
	int			i;
	t_tocken	*cur;

	cur = lst;
	redir = create_arr_for(lst, 'r');
	if (!redir)
		return (NULL);
	i = 0;
	while (cur && !is_pipe(cur))
	{
		if (is_redir(cur))
		{
			redir[i] = copy_redir(cur);
			if (!redir[i])
			{
				printf("get_redir failed\n");
				return (NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	redir[i] = NULL;
	return (redir);
}
