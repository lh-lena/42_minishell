/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:57:31 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 17:26:13 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_free_node_env(t_env *node)
{
	if (node->name)
		ft_free(&node->name);
	if (node->value)
		ft_free(&node->value);
	if (node)
		free(node);
	node = NULL;
}

void	ft_free_lst_env(t_env *lst)
{
	t_env	*temp;

	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		temp = lst->next;
		ft_free_node_env(lst);
		lst = temp;
	}
}

void	ft_delnode_env(t_env **lst, char *name)
{
	t_env	*cur;
	t_env	*prev;

	if (lst == NULL || *lst == NULL || name == NULL)
		return ;
	cur = *lst;
	prev = NULL;
	if (ft_strncmp(cur->name, "_", ft_strlen(cur->name)) == 0)
		return ;
	if (ft_strncmp(cur->name, name, ft_strlen(cur->name)) == 0)
	{
		*lst = cur->next;
		ft_free_node_env(cur);
		return ;
	}
	while (cur && (ft_strncmp(cur->name, name, ft_strlen(cur->name)) != 0))
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		return ;
	prev->next = cur->next;
	ft_free_node_env(cur);
}

void	*clean_up(t_command *res, t_data *data, t_tocken *tockns_ptr)
{
	put_error(data, "bash: syntax error near unexpected token", 2);
	free_tockns_lst(tockns_ptr);
	if (res)
		free_command_lst(res);
	data->cmd_nb = 0;
	data->pipes_nb = 0;
	return (NULL);
}
