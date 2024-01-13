#include "sh.h"

void	ft_free_data(t_data	*data)
{
	printf("data->env_lst = %p\n", data->env_lst);
	if (data->env_lst)
	{
		ft_free_lst_env(data->env_lst);
		ft_putendl_fd("free data->env_lst = OK", 1);
	}
	printf("data->argv = %p\n", data->argv);
	if (data->argv)
	{
		ft_free_arr(data->argv);
		ft_putendl_fd("free data->argv = OK", 1);
	}
	printf("data = %p\n", data);
	if (data)
	{
		free(data);
		ft_putendl_fd("free data = OK", 1);
	}
}

void	ft_free_node_env(t_env *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
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


// didn't test it
// cases:
// if del(node == first) -> lst = first->next
// change from t_env *del to name
void	ft_delnode_env(t_env **lst, char *name)
{
	t_env	*cur;
	t_env	*del;

	if (lst == NULL || name == NULL)
		return ;
	cur = *lst;
	if (ft_strncmp(cur->name, name, ft_strlen(name)) == 0)
	{
		del = cur;
		cur = cur->next;
	}
	else
	{
		while (ft_strncmp(cur->next->name, name, ft_strlen(name)) == 0)
			cur = cur->next;
		del = cur->next;
		cur->next = cur->next->next;
	}
	ft_free_node_env(del);
}

void	ft_free_arr(char **arr)
{
	char	**temp;
    int		i;

	i = 0;
	temp = arr;
	while (temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
}
