#include "sh.h"

/*This ensures that the chdir function receives an absolute path, 
whether the user provided an absolute or relative path as an argument to cd*/
// https://www.ibm.com/docs/en/zos/2.2.0?topic=descriptions-cd-change-working-directory

// arg[0] cd
// arg[1] (path)
void	cd(t_data *data, char **arg)
{
	char	*pwd;
	char	*new_pwd;

	pwd = getcwd(NULL, 0);
	printf("first pwd = %s\n", pwd);//delete
	printf("PWD:%s\n", env_get_var_value(data->env_lst, "PWD"));//delete
	printf("OLDPWD:%s\n", env_get_var_value(data->env_lst, "OLDPWD")); //delete
	env_update_val(data->env_lst, "OLDPWD", pwd);
	if (arg[1] == NULL)
	{
		new_pwd = env_get_var_value(data->env_lst, "HOME");
	}
	else
	{
		chdir(arg[1]);
		new_pwd = getcwd(NULL, 0);
		printf("pwd to given directory = %s\n", new_pwd);//delete
	}
}

/*
void pwd_command() {
    char *current_directory = getcwd(NULL, 0);

    if (current_directory != NULL) {
        printf("%s\n", current_directory);
        free(current_directory); // Free the memory allocated by getcwd
    } else {
        perror("pwd");
    }
}
*/

/*
Exit values
0 - Successful completion
1
Failure due to any of the following reasons:
No HOME directory
No previous directory
A search for directory failed
An old-to-new substitution failed
2 - An incorrect command-line option, or too many arguments
*/