/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:03:08 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/25 12:45:41 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check(char *s, int c);

void	expand_input(t_data *data)
{
	char		**temp;
	t_command	*cur;

	cur = data->cmd;
	while (cur)
	{
		if (cur->cmd)
		{
			temp = cur->cmd;
			cur->cmd = expand_arr(temp, data);
			ft_free_arr(temp);
		}
		if (cur->redir)
		{
			temp = cur->redir;
			cur->redir = expand_arr(temp, data);
			ft_free_arr(temp);
		}
		cur = cur->next;
	}
}

int	alloc_expand(char **arr, t_data *data)
{
	int		size;
	int		i;
	char	*tmp;
	char	**temp;

	size = 0;
	i = 0;
	tmp = NULL;
	temp = arr;
	while (arr[i])
	{
		if (is_quotes(temp[i]) == 0 && ft_strchr(temp[i], '$'))
		{
			tmp = expand_str(data, temp[i]);
			if (*tmp == '\0')
				size += 1;
			size += ft_count_words(tmp, 32);
			ft_free(&tmp);
		}
		else
			size++;
		i++;
	}
	return (size);
}

int	add_vars_arr(char **new, char *str, int qout)
{
	int		i;
	char	**temp;
	int		words;

	i = ft_arrsize(new);
	words = ft_count_words(str, 32);
	temp = ft_split(str, 32);
	if (!temp)
		malloc_error();
	while (qout < words)
	{
		new[i] = ft_strdup(temp[qout]);
		qout++;
		i++;
	}
	ft_free_arr(temp);
	return (qout);
}

char	**expand_arr(char **arr, t_data *data)
{
	char	**res;
	char	*str;
	int		i;
	int		k;

	res = (char **)ft_calloc((alloc_expand(arr, data) + 1), sizeof(char *));
	if (!res)
		malloc_error();
	i = 0;
	k = 0;
	while (arr[i])
	{
		str = expand_str(data, arr[i]);
		if (is_redir_str(str) && check(str, 36))
			printf("bash: %s: ambiguous redirect\n", ft_strchr(arr[i], 36));
		else if (is_quotes(arr[i]) == 0 && ft_count_words(str, 32) > 1 \
		&& !is_redir_str(str))
			k += add_vars_arr(res, str, is_quotes(arr[i]));
		else
			res[k++] = ft_strdup(str);
		ft_free(&str);
		i++;
	}
	res[k] = NULL;
	return (res);
}

//return 0 - only '$' without following char
static int	check(char *s, int c)
{
	int	i;

	i = 0;
	if (!ft_strchr(s, 36))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c && (is_whitespace(s[i + 1]) || s[i + 1] == '\0'))
			return (0);
		s++;
	}
	return (1);
}
