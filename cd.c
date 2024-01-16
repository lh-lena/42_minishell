#include "sh.h"

/* This ensures that the chdir function receives an absolute path, 
whether the user provided an absolute or relative path as an argument to cd_cmd */
// https://www.ibm.com/docs/en/zos/2.2.0?topic=descriptions-cd_cmd-change-working-directory


void	pwd_cmd(t_data *data) 
{
	if (env_isvar_name(data->env_lst, "PWD"))
	{
		data->exit_status = 0;
		printf("%s\n", env_get_var_value(data->env_lst, "PWD")); //delete
	}
	else
		data->exit_status = 1;
}

// arg[0] cd 
// arg[1] (path)  // else -> bash: cd: too many arguments 
void	cd_cmd(t_data *data, char **arg)
{
	char	*old_pwd;
	char	*new_pwd;
	size_t	size;

	new_pwd = NULL;
	size = ft_arrsize(arg);
	data->exit_status = 0;
	old_pwd = getcwd(NULL, 0);
	if (size == 1)
	{
		new_pwd = env_get_var_value(data->env_lst, "HOME"); // If there is no HOME variable, cd_cmd does not change the working directory.
		if (new_pwd)
		{
			if (chdir(new_pwd) == 0)
			{
				env_update_val(data->env_lst, "PWD", new_pwd);
				if (old_pwd)
					env_update_val(data->env_lst, "OLDPWD", old_pwd);
			}
			else
			{
				data->exit_status = 1;
				perror(strerror(errno));
			}
		}
		else
		{
			ft_putendl_fd("bash: cd: HOME not set", 2);
			data->exit_status = 1;
		}
	}
	else if (size == 2)
	{
		if (chdir(arg[1]) == 0)
		{
			new_pwd = getcwd(NULL, 0);
			if (new_pwd)
			{
				env_update_val(data->env_lst, "PWD", new_pwd);
				if (old_pwd)
					env_update_val(data->env_lst, "OLDPWD", old_pwd);
			}
			else
			{
				data->exit_status = 1;
				perror(strerror(errno));
			}
		}
		else
		{
			data->exit_status = 1;
			perror(strerror(errno));
		}
	}
	else
	{
		data->exit_status = 1;
		printf("bash: cd: too many arguments\n");
	}
	free(old_pwd);
	old_pwd = NULL;
	free(new_pwd);
	new_pwd = NULL;
}


/*
Exit values cd_cmd
0 - Successful completion
1
Failure due to any of the following reasons:
No HOME directory
No previous directory
A search for directory failed
An old-to-new substitution failed
2 - An incorrect command-line option, or too many arguments
*/
/*
ohladkov@c4c5c1:/home/ohladkov/Documents/minishell$ echo $HOME

ohladkov@c4c5c1:/home/ohladkov/Documents/minishell$ pwd
/home/ohladkov/Documents/minishell
ohladkov@c4c5c1:/home/ohladkov/Documents/minishell$ cd_cmd
bash: cd_cmd: HOME not set
ohladkov@c4c5c1:/home/ohladkov/Documents/minishell$ 
ohladkov@c4c5c1:/home/ohladkov/Documents/minishell$ echo $?
1

*/