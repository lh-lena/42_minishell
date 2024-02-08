/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_replaced_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:37:10 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/03 14:00:20 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	substitute_var(t_data *data, char **new, char **s, char *var_name);

// return a new allocated str with replaced variables
char	*get_replaced_str(t_data *data, char *s)
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
		value_len += env_isvar_name(data->env_lst, var_names[i]);
	new = replace_var_value(data, s, var_names, value_len);
	ft_free_arr(var_names);
	return (new);
}

// allocate a new_str with replaced variables, return pointer to new_str
char	*replace_var_value(t_data *data, char *s, char **var_nms, size_t val_l)
{
	char	*new;
	char	*temp;
	size_t	len;
	size_t	names_len;

	names_len = ft_arrlen(var_nms) + ft_arrsize(var_nms);
	len = ft_strlen(s) - names_len + val_l;
	temp = (char *)ft_calloc(len + 1, sizeof(char));
	if (!temp)
		malloc_error();
	new = temp;
	replace_str(temp, data, s, var_nms);
	temp[len] = '\0';
	return (new);
}

// to set allocated empty 'new' with substituted var's value
void	replace_str(char *new, t_data *data, char *s, char **var_names)
{
	int		i;

	i = -1;
	while (*s != '\0')
	{
		if (*s == '$' && (handle_name(*(s + 1)) \
		|| isvalid_var_name_char(*(s + 1))) && *s)
		{
			substitute_var(data, &new, &s, var_names[++i]);
		}
		else if (*s == '\\')
		{
			s++;
		}
		else
		{
			*new = *s;
			s++;
			new++;
		}
	}
}

static void	substitute_var(t_data *data, char **new, char **s, char *var_name)
{
	size_t	len;

	len = 0;
	*s = *s + 1;
	if (**s == '$')
	{
		data->exit_c = ft_itoa((int)getpid());
		str_copy(*new, data->exit_c);
		*new = *new + ft_strlen(data->exit_c);
		*s = *s + 1;
	}
	else if (**s == '?')
	{
		data->exit_c = ft_itoa(data->exit_status);
		str_copy(*new, data->exit_c);
		*new = *new + ft_strlen(data->exit_c);
		*s = *s + 1;
	}
	else if (isvalid_var_name_char(**s))
	{
		len = env_isvar_name(data->env_lst, var_name);
		str_copy(*new, env_var_value(data->env_lst, var_name));
		*new = *new + len;
		*s = *s + ft_strlen(var_name);
	}
	if (data->exit_c)
		ft_free(&data->exit_c);
}
