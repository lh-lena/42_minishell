/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_replaced_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:10 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 16:29:09 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// return a new allocated str with replaced variables
char	*get_replaced_str(t_env *envp, char *s)
{
	char	*new;
	char	**var_names;
	size_t	value_len;
	int		i;

	var_names = get_var_name_arr(s, '$');
	new = NULL;
	i = -1;
	value_len = 0;
	while (var_names[++i])
		value_len += env_isvar_name(envp, var_names[i]);
	new = replace_var_value(envp, s, var_names, value_len);
	ft_free_arr(var_names);
	return (new);
}

// allocate a new_str with replaced variables, return pointer to new_str
char	*replace_var_value(t_env *envp, char *s, char **var_names, size_t value_len)
{
	char	*new;
	size_t	len;
	size_t	names_len;

	names_len = ft_arrlen(var_names) + ft_arrsize(var_names);
	len = ft_strlen(s) - names_len + value_len;
	new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		perror("malloc");
	replace_str(new, envp, s, var_names);
	return (new);
}

// to set allocated empty 'new' with replaced var's value
void	replace_str(char *new, t_env *envp, char *s, char **var_names)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == '$' && isvalid_var_name_char(*(s + 1)))
		{
			s++;
			if (env_isvar_name(envp, var_names[i]))
			{
				str_copy(new, env_get_var_value(envp, var_names[i]));
				new = new + ft_strlen(env_get_var_value(envp, var_names[i]));
			}
			while (isvalid_var_name_char(*s) && *s != '\0')
				s++;
			i++;
		}
		else
		{
			*new = *s;
			s++;
			new++;
		}
	}
	*new = '\0';
}
