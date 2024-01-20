#include "sh.h"

t_env	*ft_new_node_env(char *str)
{
	t_env	*temp;
	char	**arr;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
	{
		perror("malloc");
		return (0);
	}
	arr = var_split(str, '=');
	if (!arr)
		perror("malloc");
	temp->name = (char *)ft_calloc(ft_strlen(arr[0]) + 1, 1);
	if (!temp->name)
		perror("malloc");
	ft_strlcpy(temp->name, arr[0], ft_strlen(arr[0]));
	temp->value = (char *)ft_calloc(ft_strlen(arr[1]) + 1, 1);
	if (!temp->value)
		perror("malloc");
	ft_strlcpy(temp->value, arr[1], ft_strlen(arr[1]));
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
