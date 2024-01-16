
#include "sh.h"

// input[0] input[1] input[1]
// export   var=val  var=val
void	export(t_data *data, char **input)
{
	size_t	i;
	char	*temp;

	i = 0;
	data->exit_status = 0;
	while (++i < ft_arrsize(input))
	{
		if (is_quotes(input[i]) == -1)
		{
			data->exit_status = 5;
			printf("bash: export: Quotes are not correctly closed\n");
		}
		else if (isvalid_export_input(input[i]))
		{
			temp = export_execution(data, input[i]);
			if (temp != NULL)
			{
				free(input[i]);
				input[i] = temp;
			}
			env_replace_or_create_node(data->env_lst, input[i]);
		}
		else if (!isvalid_export_input(input[i]))
		{
			data->exit_status = 1;
			printf("bash: export: `%s': not a valid identifier\n", input[i]);
		}
	}
}

// return 5 - if quotes don't close
char	*export_execution(t_data *data, char *input)
{
	char	*temp_new;

	temp_new = NULL;
	if (is_quotes(input) == 1 || is_quotes(input) == 2)
	{
		printf("is_quotes(input) == 2\n");
		return (0);
	}
	else if (ft_strchr(input, '$'))
	{
		temp_new = get_replaced_str(data->env_lst, input); // malloc
		if (!temp_new)
			return (NULL);
	}
	return (temp_new);
}

void	env_replace_or_create_node(t_env *envp, char *input)
{
	char	**var_val;
	t_env	*new;

	var_val = var_split(input, '=');
	if (env_update_val(envp, var_val[0], var_val[1]))
		ft_free_arr(var_val);
	else
	{
		new = ft_new_node_env(input);
		if (!new)
			perror("malloc");
		ft_lstadd_back_env(&envp, new);
		ft_free_arr(var_val);
	}
}

	// else if (is_quotes(input) == 1 || is_qoutes(input) == 2)
	// 	temp_new = handle_qoutes(data->env_lst, input);

/* 
	else if (is_quotes(input) == 1)
	{
		printf("is_quotes(input) == 1\n");
		return (0);
	}
	else if (is_quotes(input) == 2)
	{
		printf("is_qoutes(input) == 2\n");
		return (0);
	}
 */

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
