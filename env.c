/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:43 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/18 15:31:48 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*copy_var(t_data *data, char *name, char *value);

// creat a linked list of enviroment variables 
t_env	*ft_getenv(char **envp)
{
	t_env	*env;
	t_env	*new;
	size_t	size;
	size_t	i;

	env = NULL;
	size = ft_arrsize(envp);
	new = NULL;
	i = 0;
	while (i < size)
	{
		new = ft_new_node_env(envp[i]);
		if (!new)
			return (NULL);
		ft_lstadd_back_env(&env, new);
		i++;
	}
	env_update_val(env, "_", "/usr/bin/env");
	return (env);
}

void	env_print(t_data *data)
{
	data->exit_status = 0;
	ft_print_lst_env(&data->env_lst, 0);
}

char	**new_envp(t_data *data)
{
	char	**new_envp;
	t_env	*temp;
	size_t	i;
	size_t	j;

	if (!data->env_lst)
		return (NULL);
	i = ft_lstsize_env(data->env_lst);
	temp = data->env_lst;
	new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new_envp)
		malloc_error();
	j = -1;
	while (temp != NULL)
	{
		new_envp[++j] = copy_var(data, temp->name, temp->value);
		if (!new_envp[j])
			malloc_error();
		temp = temp->next;
	}
	new_envp[++j] = NULL;
	return (new_envp);
}

static char	*copy_var(t_data *data, char *name, char *value)
{
	char	*env_str;
	char	*eq;
	size_t	len;

	(void)data;
	len = ft_strlen(name) + ft_strlen(value) + 1;
	env_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!env_str)
		malloc_error();
	eq = "=";
	ft_strlcpy(env_str, name, ft_strlen(name) + 1);
	ft_strlcat(env_str, eq, ft_strlen(name) + ft_strlen(eq) + 1);
	ft_strlcat(env_str, value, len + 1);
	return (env_str);
}
