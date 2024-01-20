/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:43 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 16:24:03 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh.h"

// creat a linked list of enviroment variables 
t_env *ft_getenv(char **envp)
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
	if (env_update_val(env, "_", "/usr/bin/env") == 0)
		perror("error var not found");
	return (env);
}

void	env_print(t_data *data)
{
	ft_print_lst_env(&data->env_lst, 0);
}

/*
 -- env updates --

_=/usr/bin/env
ohladkov@c4b7c6:~/Documents/minishell$ echo $_
env
ohladkov@c4b7c6:~/Documents/minishell$ export _=ls
ohladkov@c4b7c6:~/Documents/minishell$ echo $_
_=ls
ohladkov@c4b7c6:~/Documents/minishell$ ls
ohladkov@c4b7c6:~/Documents/minishell$ echo $_
ls

*/


/* 
manipulate env:
- 
*/
