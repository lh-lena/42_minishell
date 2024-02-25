/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:53 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/22 11:57:08 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static size_t	count_len(t_data *data, char *s);
static void		add_len_dqoutes(t_data *data, char **str);
static void		add_len_sqoutes(t_data *data, char **str);
static void		add_len_variable(t_data *data, char **str);

// return poiner to a new_str, escape qoutes and substitute evn_variables 
char	*substitute_str(t_data *data, char *str)
{
	char	*new;
	char	*temp;
	size_t	len;

	if (!str)
		return (NULL);
	temp = str;
	len = count_len(data, temp);
	new = NULL;
	new = copy_modified_str(data, str, len);
	if (!new)
		malloc_error();
	return (new);
}

static size_t	count_len(t_data *data, char *s)
{
	data->len = 0;
	while (*s != '\0')
	{
		if ((*s == 34 && *(s + 1) == 34) || (*s == 39 && *(s + 1) == 39))
			s = s + 2;
		else if (*s == 39 && *s)
			add_len_sqoutes(data, &s);
		else if (*s == 34)
			add_len_dqoutes(data, &s);
		else if (*s == '$' && (handle_name(*(s + 1)) \
		|| isvalid_var_name_char(*(s + 1))))
			add_len_variable(data, &s);
		else if (*s == '\\')
			s++;
		else
		{
			data->len += 1;
			s++;
		}
	}
	return (data->len);
}

// str -> 'input'
static void	add_len_sqoutes(t_data *data, char **str)
{
	*str = *str + 1;
	while (**str != 39)
	{
		data->len += 1;
		*str = *str + 1;
	}
	*str = *str + 1;
}

// str -> "input"
static void	add_len_dqoutes(t_data *data, char **str)
{
	*str = *str + 1;
	while (**str != '\"')
	{
		if (**str == '$' && (handle_name(*(*str + 1)) \
		|| isvalid_var_name_char(*(*str + 1))))
		{
			add_len_variable(data, str);
			if (**str == 34)
				break ;
		}
		else
		{
			*str = *str + 1;
			data->len += 1;
		}
	}
	*str = *str + 1;
}

// str -> $VAR_NAME | count VAR_NAME's value
static void	add_len_variable(t_data *data, char **str)
{
	*str = *str + 1;
	if (**str == '?')
	{
		data->exit_c = ft_itoa(data->exit_status);
		data->len += ft_strlen(data->exit_c);
		*str = *str + 1;
	}
	else
	{
		data->len += env_isvar_name(data, *str);
		while (isvalid_var_name_char(**str))
			*str = *str + 1;
	}
	if (data->exit_c)
		ft_free(&data->exit_c);
}
