/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:13:07 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 17:26:15 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_command	*create_cmd_node(t_tocken *lst)
{
	t_command	*res;
	char		**cmd;
	char		**redir;

	res = NULL;
	cmd = get_command(lst);
	redir = get_redir(lst);
	if (!cmd && !redir)
		return (NULL);
	res = (t_command *)malloc(sizeof(t_command));
	if (!res)
		return (malloc_error());
	res->cmd = cmd;
	res->redir = redir;
	res->next = NULL;
	return (res);
}

int	check_redir(t_tocken *tkn)
{
	int		size;
	char	*str;

	str = tkn->begin;
	size = tkn->end - tkn->begin;
	if (size < 2)
		return (-1);
	if (size == 2 && str[0] == str[1])
		return (-1);
	if (str[0] == str[1])
		str++;
	str++;
	while (is_whitespace(*str) && str != tkn->end)
		str++;
	if (str == tkn->end)
		return (-1);
	return (0);
}

int	check_syntax(t_data *data, t_tocken *tkn)
{
	t_tocken	*cur;

	(void)data;
	if (is_pipe(tkn))
		return (-1);
	cur = tkn;
	while (cur && !is_pipe(cur))
	{
		if (is_redir(cur))
		{
			if (check_redir(cur) == -1)
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

void	create_add_cmd(t_command **res, t_data *data, t_tocken *tockns)
{
	t_command	*cur;

	cur = create_cmd_node(tockns);
	if (cur)
	{
		add_cmd(res, cur);
		data->cmd_nb++;
	}
}

t_command	*parse_input(t_data *data)
{
	t_command	*res;
	t_tocken	*tockns;
	t_tocken	*tockns_ptr;

	res = NULL;
	tockns = get_tockens(data->input);
	if (!tockns)
		return (NULL);
	tockns_ptr = tockns;
	if (check_syntax(data, tockns) == -1)
		return (clean_up(res, data, tockns));
	create_add_cmd(&res, data, tockns);
	while (tockns)
	{
		if (is_pipe(tockns))
		{
			if (!tockns->next || check_syntax(data, tockns->next) == -1)
				return (clean_up(res, data, tockns_ptr));
			data->pipes_nb++;
			create_add_cmd(&res, data, tockns->next);
		}
		tockns = tockns->next;
	}
	free_tockns_lst(tockns_ptr);
	return (res);
}
