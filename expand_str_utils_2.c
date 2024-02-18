/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:53 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/12 11:54:07 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	copy_sqoutes(char **new, char **str, t_data *data);
static void	copy_dqoutes(char **new, char **str, t_data *data);
static void	substitute_vars(char **new, char **str, t_data *data);
static void	strptr_copy(char **dst, char **src);

// return pointer to modified string
char	*copy_modified_str(t_data *data, char *str, size_t len)
{
	char	*new;
	char	*temp_new;

	temp_new = (char *)ft_calloc((len + 1), sizeof(char));
	if (!temp_new)
		malloc_error();
	new = temp_new;
	while (*str)
	{
		if (*str == 39 && *str)
			copy_sqoutes(&temp_new, &str, data);
		else if (*str == 34 && *str)
			copy_dqoutes(&temp_new, &str, data);
		else if (*str == '$' && (handle_name(*(str + 1))\
		|| isvalid_var_name_char(*(str + 1))))
			substitute_vars(&temp_new, &str, data);
		else if (*str == '\\' && *(str + 1) != '\\')
			str++;
		else
			strptr_copy(&temp_new, &str);
	}
	*temp_new = '\0';
	return (new);
}

static void	copy_sqoutes(char **new, char **str, t_data *data)
{
	(void)data;
	*str = *str + 1;
	while (**str != 39)
	{
		**new = **str;
		*str = *str + 1;
		*new = *new + 1;
	}
	*str = *str + 1;
}

static void	copy_dqoutes(char **new, char **str, t_data *data)
{
	*str = *str + 1;
	while (**str != 34 && **str)
	{
		if (**str == '$' && (*(*str + 1) == '?' \
		|| isvalid_var_name_char(*(*str + 1))))
		{
			substitute_vars(new, str, data);
		}
		else
		{
			**new = **str;
			*str = *str + 1;
			*new = *new + 1;
		}
	}
	*str = *str + 1;
}

static void	substitute_vars(char **new, char **str, t_data *data)
{
	size_t	size;

	size = 0;
	if (**str == '$' && *(*str + 1) == '?')
	{
		data->exit_c = ft_itoa(data->exit_status);
		*str = *str + 2;
		str_copy(*new, data->exit_c);
		*new = *new + ft_strlen(data->exit_c);
	}
	else if (**str == '$' && isvalid_var_name_char(*(*str + 1)))
	{
		*str = *str + 1;
		size = env_isvar_name(data->env_lst, *str);
		str_copy(*new, env_var_value(data->env_lst, *str));
		*new = *new + size;
		while (isvalid_var_name_char(**str))
			*str = *str + 1;
	}
	if (data->exit_c)
		ft_free(&data->exit_c);
}

// copy_str
static void	strptr_copy(char **dst, char **src)
{
	**dst = **src;
	*dst = *dst + 1;
	*src = *src + 1;
}
