
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

// if there is var in the envp, return len of its value, otherwise 0
int	env_isvar_name(t_env *envp, char *name)
{
	t_env	*temp;

	temp = envp;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
			return (ft_strlen(temp->value));
		temp = temp->next;
	}
	return (0);
}

// to update a value existed variable, if no one found return 0
int	env_update_val(t_env *envp, char *name, char *value)
{
	while (envp != NULL)
	{
		if (ft_strncmp(envp->name, name, ft_strlen(name)) == 0)
		{
			free(envp->value);
			envp->value = (char *)ft_calloc(ft_strlen(value) + 1, sizeof(char));
			ft_strlcpy(envp->value, value, ft_strlen(value));
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	env_print(t_data *data)
{
	ft_print_lst_env(&data->env_lst);
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