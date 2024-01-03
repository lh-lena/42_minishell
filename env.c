#include "sh.h"

t_env *ft_getenv(char **envp)
{
	t_env	*env;
	t_env	*new;
	size_t	size;
	int		i;

	env = NULL;
	size = ft_arrsize(envp);
	new = NULL;
	i = 0;
	while (size)
	{
		new = ft_lstnew(envp[i]);
		if (!new)
			return (NULL);
		ft_lstadd_back(&env, new);
		size--;
		i++;
	}
	return (env);
}

void	env_tr(t_data	*data)
{
	t_env	*env;

	env = ft_getenv(data->envp);
	print_lst(env);
}