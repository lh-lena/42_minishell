#include "sh.h"

int	isvalid_export_input(char *str)
{
	char	**var_val;

	if (!str)
		return (0);
	if (!ft_strchr(str, '='))
		return (0);
	var_val = var_split(str, '='); // malloc
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
		printf("Error isvalid_var_name_str, start with digit\n"); // exit_st 1
		return (0);
	}
	while (str[i])
	{
		if (!isvalid_var_name_char(str[i]))
		{
			printf("Error isvalid_var_name_str\n"); //delete
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
	int		i;
	int		res;

	i = -1;
	res = 0;
	while (++i < (int)ft_strlen(value) && value[i])
	{
		if (value[i++] == 39) // iteration ok?
		{
			res = 1;
			while (value[i] != 39)
			{	
				if (value[i] == '\0')
					return (-1);
				i++;
			}
		}
		else if (value[i++] == 34)
		{
			res = 2;
			while (value[i] != 34)
			{	
				if (value[i] == '\0')
					return (-1);
				i++;
			}
		}
	}
	return (res);
}
