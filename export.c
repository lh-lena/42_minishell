
#include "sh.h"

//       input[1] input[1] 
// input: var=val var=val 
// todo: 1.check the input if ok-> 2.
//		2. check if var exist -> change value ; else-> 3.
// 		3. create a new var_node and add to the end of the env_list
// check for quots
// works only input: var=val and for invalid identifier

void	export(t_data *data, char **input)
{
	int		i;
	int		size;

	i = 0;
	size = ft_arrsize(input);
	while (input[++i] < size - 1)
	{
		if (!isvalid_export_input(input[1]))
		{
			data->exit_status = 1;
			printf("bash: export: `%s': not a valid identifier\n", input[1]);
		}
		else if (isvalid_export_input(input[i]))
		{
			data->exit_status = export_execution(data, input[i]);
			if (data->exit_status == 5)
				printf("bash: export: Quotes are not correctly closed\n");
		}
		else
			break ;
	}
}

int	isvalid_export_input(char *str)
{
	char	**var_val;
	int		i;

	if (!ft_strchr(str, '='))
		return (0);
	var_val = ft_split(str, '=');
	if (!var_val)
		perror(malloc);
	i = 0;
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
		printf("Error isvalid_var_name_str, start with digit/=\n");
		return (0);
	}
	while (str[i] != '=')
	{
		// if (!ft_isalnum(str[i]) && str[i] != 95)
		if (!isvalid_var_name_char(str[i]))
		{
			printf("Error isvalid_var_name_str\n");
			return (0);
		}
		i++;
	}
	return (1);
}

// return 5 - if quotes don't close, 
int	export_execution(t_data *data, char *input)
{
	t_env	*new;
	char	*temp_new;

	temp_new = NULL;
	if (is_qoutes(input) == -1)
		return (5); // Quotes are not correctly closed
	else if (is_quotes(input) == 1 || is_qoutes(input) == 2)
		temp_new = handle_qoutes(data->env_lst, input);
	else if (ft_strchr(input, '$'))
		temp_new = replace_var_value(data->env_lst, input);
	else
		temp_new = input;
	new = ft_new_node_env(temp_new);
	if (!new)
		return (1);
	ft_lstadd_back_env(&data->env_lst, new);
	// free(temp_new);
	// temp_new = NULL;
	return (0);
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
	while (++i < len && value[i])
	{
		if (value[++i] == 39) // iteration ok?
		{
			res = 1;
			while (value[++i] != 39 && value[i]);
			if (value[i + 1] == '\0')
				return (-1);
		}
		else if (value[++i] == 34)
		{
			res = 2;
			while (value[++i] != 34 && value[i]);
			if (value[i + 1] == '\0')
				return (-1);
		}
	}
	return (res);
}

// char	*handle_quotes(t_env *envp, char *input)
// {
// 	char	*new;
// 	int		i;

// 	i = -1;
// 	new = (char *)calloc((ft_strlen(input) + 1), sizeof(char));
// 	if (!new)
// 		perror("malloc");
// 	while (input[++i])
// 	{
// 		new[i] = input[i];
// 	}
// 	return (new);
// }

// str: varname=fkjfj$lkd return a new allocated str with replaced variable
char	*replace_var_value(t_env *envp, char *str)
{
	char	*new;
	char	**name;
	int		value_len;

	name = get_var_name(str); // malloc
	new = NULL;
	value_len = env_isvar_name(envp, name);
	if (value_len)
		new = ;
	else
	{
		new = (char *)malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(name)));
		if (!new)
			perror("malloc");
	}
	free(name);
	name = NULL;
	return (new);
}

// return poiner to array of allocated VAR's name from the given string
char	**get_var_name(char *str)
{
	char	**name;
	size_t	len;
	size_t	j;
	size_t	k;
	int		n;

	len = 0;
	j = 0;
	n = -1;
	k = 0;
	while (str[j])
	{
		j = k;
		if (str[j] == '$')
		{
			j++;
			k = j;
			while ((ft_isalnum(str[k++]) || str[k++] == 95) && str[k++])
			{
				len++;
				// k++;
			}
			name[++n] = ft_substr(str, j, len);
			printf("n = %d", n);
		}
		j++;
	}
	if (!name)
		perror("malloc (cut_var_name)");
	return (name);
}
// Rules for Naming variable name ---> // https://bash.cyberciti.biz/guide/Rules_for_Naming_variable_name

/*

1. no spaces on either side of the equal sign	|OK
bash-3.2$ export no  =10
bash: export: `=10': not a valid identifier // must be checked on Linux

2. You can define a NULL variable as follows
$ export vech= or vech=""
$ echo $vech

$
3. valid VAR_NAME:			|OK
a-zA-Z_0-9				
_GREP=/usr/bin/grep #valid
-- invalid name --
?,* 
bash-3.2$ export ?no=10
bash: export: `?no=10': not a valid identifier
bash-3.2$ export 1no=10
bash: export: `1no=10': not a valid identifier

out*put=/tmp/filename.txt #invalid

---- valid input ----
bash-3.2$ export var='ok' 'ko||' // use only first command
bash-3.2$ echo $var
bash-3.2$ ok


--- Invalid value ---
bash-3.2$ export var="ok''" "ko||"
bash: export: `ko||': not a valid identifier
bash-3.2$ export var='ok' "ko||"
bash: export: `ko||': not a valid identifier
*/