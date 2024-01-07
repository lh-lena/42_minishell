
#include "sh.h"


// input: var=val
// todo: 1.check the input if ok-> 2.
//		2. check if var exist -> change value ; else-> 3.
// 		3. create a new var_node and add to the end of the env_list
// check for quats
void	export(t_data *data, char *input)
{
	int	name_valid;
	int	input_valid;

	if (input)
	{
		input_valid = 0;
		name_valid = 0;
		input_valid = isvalid_export_input(input);
		name_valid = isvalid_var_name(input);
		if (input_valid && name_valid)
		{
			data->exit_status = export_execution(data, input);
		}
		else
		{
			data->exit_status = 0;
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(input, 1);
			ft_putendl_fd("': not a valid identifier", 1);
		}
	}
	else
		perror("invalid export input");
}

int	isvalid_export_input(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// valid var_name-> a-zA-Z0-9_
int	isvalid_var_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str) || *str == '=')
		return (0);
	while (str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != 95)
			return (0);
		i++;
	}
	return (1);
}

// if VAR exist in enveironment -> replace, else -> append a new one
int	export_execution(t_data *data, char *input)
{
	char	**var_val;
	int		i;
	t_env	*new_var;

	i = 0;
	var_val = ft_split(input, '=');
	if (!var_val)
		perror("malloc");
	data->exit_status = 0;
	if (env_update_val(data->env_lst, var_val[0], var_val[1]))
	{
		data->exit_status = 1;
	}
	else
	{
		data->exit_status = 1;
		new_var = ft_new_node_env(input);
		if (!new_var)
			perror("malloc");
		ft_lstadd_back_env(&data->env_lst, new_var);
	}
	return (data->exit_status);
}

// Rules for Naming variable name ---> // https://bash.cyberciti.biz/guide/Rules_for_Naming_variable_name

/*
1. no spaces on either side of the equal sign
bash-3.2$ export no  =10
bash: export: `=10': not a valid identifier // must be checked on Linux

2. You can define a NULL variable as follows
$ export vech= or vech=""
$ echo $vech

$
3. valid VAR_NAME:
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