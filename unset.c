
#include "sh.h"

//    input[0]  [1]  [2]
// input: var1 var2 var3
void	unset(t_data *data, char **input)
{
	int		i;

	data->exit_status = 0; // bash doesn't react at all, always success
	i = 0;
	while (input[++i])
	{
		if (env_isvar_name(data->env_lst, input[i]))
			ft_delnode_env(&data->env_lst, input[i]);
		else
			perror("var_name not found"); // delete
	}
}
