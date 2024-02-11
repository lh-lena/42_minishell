/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:07:07 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/28 18:24:31 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_env	*ft_new_node_env(char *str)
{
	t_env	*temp;
	char	**arr;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
		malloc_error();
	arr = var_split(str, '=');
	if (!arr)
		malloc_error();
	temp->name = (char *)ft_calloc(ft_strlen(arr[0]) + 1, 1);
	if (!temp->name)
		malloc_error();
	ft_strlcpy(temp->name, arr[0], ft_strlen(arr[0]) + 1);
	temp->value = (char *)ft_calloc(ft_strlen(arr[1]) + 1, 1);
	if (!temp->value)
		malloc_error();
	ft_strlcpy(temp->value, arr[1], ft_strlen(arr[1]) + 1);
	temp->next = NULL;
	ft_free_arr(arr);
	return (temp);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*cur;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

size_t	ft_lstsize_env(t_env *lst)
{
	t_env	*temp;
	size_t	i;

	if (lst == 0)
		return (0);
	temp = lst;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

size_t	ft_lstsize_node(t_env *lst)
{
	t_env	*temp;
	size_t	i;

	if (lst == 0)
		return (0);
	temp = lst;
	i = 0;
	while (temp)
	{
		i += ft_strlen(temp->name);
		i += ft_strlen(temp->value);
		temp = temp->next;
	}
	i += ft_lstsize_env(lst);
	return (i);
}

void	ft_print_lst_env(t_env **lst, int arg)
{
	t_env	*temp;
	size_t	size;
	size_t	i;

	(void)arg;
	temp = *lst;
	size = ft_lstsize_env(*lst);
	i = 0;
	while (i < size)
	{
		ft_putstr_fd(temp->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(temp->value, 1);
		ft_putchar_fd('\n', 1);
		temp = temp->next;
		i++;
	}
	// to del
	if (!lst)
		printf("lst = NULL\n");
}
