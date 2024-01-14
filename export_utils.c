#include "sh.h"

int	isvalid_export_input(char *str)
{
	char	**var_val;

	if (!ft_strchr(str, '='))
		return (0);
	var_val = ft_split(str, '='); // malloc
	if (!var_val)
		perror("malloc");
	if (!isvalid_var_name_str(var_val[0]))
	{
		ft_free_arr(var_val);
		return (0);
	}
	ft_free_arr(var_val);
	return (1);
}

// valid var_name-> a-zA-Z0-9_
int	isvalid_var_name_str(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str) || *str == '=')
	{
		printf("Error isvalid_var_name_str, start with digit\n");
		return (0);
	}
	while (str[i])
	{
		if (!isvalid_var_name_char(str[i]))
		{
			printf("Error isvalid_var_name_str\n");
			return (0);
		}
		i++;
	}
	return (1);
}

// valid var_name-> a-zA-Z0-9_
int isvalid_var_name_char(int c)
{
	if (!ft_isalnum(c) && c != 95)
	{
		return (0);
	}
	return (1);
}

// return 0 - if no quotes, -1 - if qouts don't close, 1 = ', 2 = "
int	is_quotes(char *value)
{
	size_t	len;
	int		i;
	int		res;

	i = -1;
	len = ft_strlen(value);
	res = 0;
	while (++i < (int)len && value[i])
	{
		if (value[i] == 39) // iteration ok?
		{
			if (ft_strrchr(value, 39) && (ft_strchr(value, 39) != ft_strrchr(value, 39)))
				res = 1;
			else
				return (-1);
		}
		else if (value[i] == 34)
		{
			if (ft_strrchr(value, 34) && (ft_strchr(value, 34) != ft_strrchr(value, 34)))
				res = 2;
			else
				return (-1);
		}
	}
	return (res);
}
