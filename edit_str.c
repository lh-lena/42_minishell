/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:53 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 16:20:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static size_t count_len(t_env *envp, char *str);
static size_t count_len_dqoutes(t_env *envp, char *str);
static size_t count_len_sqoutes(char *str);
static char *copy_modified(t_env *envp, char *str, size_t len);

// return poiner to a new_str, cleaned from qoutes and replace evn_variables
char	*edit_str(t_env *envp, char *str)
{
	char	*new;
	size_t	len;

	if (!str)
		return (NULL);
	len = count_len(envp, str);
	new = NULL;
	new = copy_modified(envp, str, len);
	if (!new)
		perror("malloc edit_str");
	return (new);
}

static size_t count_len(t_env *envp, char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39 && str[i + 1])
		{
			len += count_len_sqoutes(str + i);
			i += count_len_sqoutes(str + i);
			i++;
		}
		else if (str[i] == 34 && str[i + 1])
		{
			len += count_len_dqoutes(envp, str + i);
			while (str[++i] != 34);
		}
		else
			len++;
		i++;
	}
	return (len);
}

// str -> 'input'
static size_t count_len_sqoutes(char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 1;
	while (str[i] != 39 && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

// str -> "input"
static size_t count_len_dqoutes(t_env *envp, char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 1;
	while (str[i] != 34 && str[i])
	{
		if (str[i] == '$' && isvalid_var_name_char(str[i + 1]))
		{
			i++;
			len += env_isvar_name(envp, str + i);
			while (isvalid_var_name_char(str[i]))
				i++;
		}
		i++;
		len++;
	}
	printf("len = %zu\n", len);
	return (len);
}

// return poiner to modified string 
static char *copy_modified(t_env *envp, char *str, size_t len)
{
	char	*new;
	char	*temp_new;

	temp_new = (char *)ft_calloc((len + 1), sizeof(char));
	if (!temp_new)
		perror("malloc");
	new = temp_new;
	while (*str)
	{
		if (*str == 39 && *str)
		{
			str++;
			while (*str != 39 && *str)
			{
				*temp_new = *str;
				str++;
				temp_new++;
			}
			str++;
		}
		else if (*str == 34 && *str)
		{
			str++;
			while (*str != 34 && *str)
			{
				if (*str == '$' &&  isvalid_var_name_char(*(str + 1)))
				{
					str++;
					str_copy(temp_new, env_get_var_value(envp, str));
					temp_new = temp_new + ft_strlen(env_get_var_value(envp, str));
					while (isvalid_var_name_char(*str))
						str++;
				}
				else
				{
					*temp_new = *str;
					str++;
					temp_new++;
				}
			}
			str++;
		}
		else
		{
			*temp_new = *str;
			str++;
			temp_new++;
		}
	}
	*temp_new = '\0';
	return (new);
}
