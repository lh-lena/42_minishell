/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:53 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/02 14:47:26 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// to update a value existed variable, if no one found return 0
int	env_update_val(t_env *envp, char *name, char *value)
{
	while (envp != NULL)
	{
		if (ft_strncmp(envp->name, name, ft_strlen(envp->name)) == 0)
		{
			free(envp->value);
			envp->value = (char *)ft_calloc(ft_strlen(value) + 1, sizeof(char));
			ft_strlcpy(envp->value, value, ft_strlen(value) + 1);
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	env_replace_or_create_node(t_env *envp, char *input)
{
	char	**var_val;
	t_env	*new;

	var_val = var_split(input, '=');
	if (env_update_val(envp, var_val[0], var_val[1]))
		ft_free_arr(var_val);
	else
	{
		new = ft_new_node_env(input);
		if (!new)
			malloc_error();
		ft_lstadd_back_env(&envp, new);
		ft_free_arr(var_val);
	}
}

// return VAR's VALUE, if no found return NULL
char	*env_var_value(t_env *envp, char *str)
{
	t_env	*temp;
	char	*name;

	if (!str)
		return (NULL);
	name = copy_var_name(str);
	if (!name)
		return (NULL);
	temp = envp;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(temp->name)) == 0)
		{
			free(name);
			return (temp->value);
		}
		temp = temp->next;
	}
	free(name);
	return (NULL);
}

// if there is var in the envp, return len of its value, otherwise 0
size_t	env_isvar_name(t_env *envp, char *str)
{
	t_env	*temp;
	char	*name;

	if (!str)
		return (0);
	name = copy_var_name(str);
	if (!name)
		return (0);
	temp = envp;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(temp->name)) == 0)
		{
			free(name);
			if (ft_strlen(temp->value))
				return (ft_strlen(temp->value));
			else
				return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

char	*copy_var_name(char *str)
{
	char	*new;
	size_t	i;

	i = 0;
	while (isvalid_var_name_char(str[i]) && str[i])
		i++;
	new = (char *)ft_calloc(i + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (isvalid_var_name_char(str[i]) && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
