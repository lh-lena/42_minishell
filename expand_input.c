#include "sh.h"

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
			size += ft_count_words(tmp, 32);
			ft_free(&tmp);
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	**expand_arr(char **arr, t_data *data)
{
	char	**res;
	char	*str;
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = alloc_expand(arr, data);
	res = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	j = 0;
	k = 0;
	str = NULL;
	temp = NULL;
	while (arr[i])
	{
		j = is_quotes(arr[i]);
		str = expand_str(data, arr[i]);
		if (j == 0 && ft_count_words(str, 32) > 1 && !is_redir_str(str))
		{
			temp = ft_split(str, 32);
			while (j < ft_count_words(str, 32))
			{
				res[k] = ft_strdup(temp[j]);
				k++;
				j++;
			}
			ft_free_arr(temp);
		}
		else if (ft_count_words(str, 32) > 1 && is_redir_str(str) && ft_strchr(arr[i], 36))
			printf("bash: %s: ambiguous redirect\n", ft_strchr(arr[i], 36));
		else
		{
			res[k] = ft_strdup(str);
			k++;
		}
		ft_free(&str);
		i++;
	}
	res[k] = NULL;
	return (res);
}

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
