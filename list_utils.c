#include "sh.h"

t_env	*ft_lstnew(char	*str)
{
	t_env	*temp;
	char	**arr;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
		perror("malloc");
	arr = ft_split(str, '=');
	temp->name = arr[0];
	temp->value = arr[1];
	temp->next = NULL;
	free(arr);
	return (temp);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
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

void	ft_free_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

// didn't test it
// cases:
// if del(node == first) -> lst = first->next
// change from t_env *del to name
void	ft_delnode(t_env **lst, char *name)
{
	t_env	*cur;
	t_env	*del;

	if (lst == NULL || name == NULL)
		return ;
	cur = *lst;
	if (cur->name == name)
	{
		del = cur;
		cur = cur->next;
	}
	else
	{
		while (cur->next->name != name)
			cur = cur->next;
		del = cur->next;
		cur->next = cur->next->next;
	}
	ft_free_node(del);
}

size_t	ft_lstsize(t_env *lst)
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

void	print_lst(t_env *lst)
{
	t_env	*temp;
	size_t	size;
	size_t	i;

	temp = lst;
	size = ft_lstsize(lst);
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
	if (!lst)
		printf("lst = NULL\n");
}
