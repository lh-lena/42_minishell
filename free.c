/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:24 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/11 22:41:13 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_free_data(t_data	*data)
{
	// printf("data->env_lst = %p\n", data->env_lst); // delete
	if (data->env_lst)
	{
		ft_free_lst_env(data->env_lst);
		// ft_putendl_fd("free data->env_lst = OK", 1); // delete
	}
	// printf("data->new_envp = %p\n", data->new_envp); // delete
	if (data->new_envp)
	{
		ft_free_arr(data->new_envp);
		// ft_putendl_fd("free data->new_envp = OK", 1); // delete
	}
	// printf("data->cmd = %p\n", data->cmd); // delete
	if (data->cmd)
	{
		free_command_lst(data->cmd);
		// ft_putendl_fd("free data->cmd = OK", 1); // delete
	}
	// printf("data = %p\n", data); // delete
	if (data)
	{
		free(data);
		// ft_putendl_fd("free data = OK", 1); // delete
	}
}

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
	// printf("node to delete -> %s=%s\n", cur->name, cur->value); // delete
	ft_free_node_env(cur);
}

void	ft_free_arr(char **arr)
{
	char	**temp;
	int		i;

	i = 0;
	if (arr != NULL)
	{
		temp = arr;
		while (temp[i])
		{
			if (temp[i])
			{
				ft_free(&temp[i]);
			}
			i++;
		}
		free(temp);
		temp = NULL;
	}
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
