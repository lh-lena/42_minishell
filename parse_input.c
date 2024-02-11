/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:13:07 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/08 19:06:41 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_redir(t_tocken *tkn)
{
	int		i;
	int		ofset;
	int		size;
	char	*str;
	char	*res;

	res = NULL;
	ofset = 0;
	str = tkn->begin;
	size = tkn->end - tkn->begin;
	if (size > 2)
	{
		while (is_whitespace(str[ofset + 2]) && &str[ofset + 2] != tkn->end)
			ofset++;
	}
	res = (char *)malloc((size - ofset + 1) * sizeof(char));
	if (!res)
		return (malloc_error());
	i = 0;
	while (i < 2)
	{
		res[i] = str[i];
		i++;
	}
	while (&str[i + ofset] != tkn->end)
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
			i++;
		}
		cur = cur->next;
	}
	redir[i] = NULL;
	return (redir);
}

t_command	*create_cmd_node(t_tocken *lst)
{
	t_command	*res;
	char		**cmd;
	char		**redir;

	cmd = get_command(lst);
	// if (!cmd)
	// 	return (NULL);
	redir = get_redir(lst);
	res = (t_command *)malloc(sizeof(t_command));
	if (!res)
		return (malloc_error());
	res->cmd = cmd;
	res->redir = redir;
	res->next = NULL;
	return (res);
}

t_command	*parse_input(t_data *data) //char *str)
{
	t_command	*res;
	t_command	*cur;
	t_tocken	*tockns;
	t_tocken	*tockns_ptr;

	res = NULL;
	tockns = get_tockens(data->input);
	if (!tockns)
		return (NULL);
	tockns_ptr = tockns;
	cur = create_cmd_node(tockns);
	if (cur)
	{
		add_cmd(&res, cur);
		data->cmd_nb++;
	}
	while (tockns)
	{
		if (is_pipe(tockns) && tockns->next)
		{
			if (is_pipe (tockns->next))
			{
				printf("syntax error");
				return (NULL);
			}
			data->pipes_nb++;
			cur = create_cmd_node(tockns->next);
			if (cur)
			{
				add_cmd(&res, cur);
				data->cmd_nb++;
			}
		}
		tockns = tockns->next;
	}
	//printf("number of pipes= %i\n", data->pipes_nb);
	free_tockns_lst(tockns_ptr);
	return (res);
}
