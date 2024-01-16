// https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/#:~:text=The%20%24%3F%20(dollar%20question%20mark)%20is%20the%20exit%20status%20of,executed%20command%20failed%20or%20not.
// 0 - succesful execution

#include "sh.h"

static int	ft_calc_exit_status(char *str);
static int	check_exit_arg(t_data *data, char *str);

int	is_exit(t_data *data)
{
	char	**arr;
	int		size;
	int		i;

	arr = ft_split(data->input, ' ');
	if (!arr)
		perror("malloc");
	size = ft_arrsize(arr);
	i = 0;
	if (ft_strncmp(arr[0], "exit", ft_strlen(arr[0])) == 0) // delete
	{
		i = 1;
		if (size == 2)
			i = check_exit_arg(data, arr[1]);
		else if (size > 2)
		{
			i = 0;
			data->exit_status = 1;
			printf("exit\nbash: exit: too many arguments\n"); // doesn't exit for real
		}
	}
	else
		i = 0;
	ft_free_arr(arr);
	return (i);
}

static int	check_exit_arg(t_data *data, char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit_str(str))
		data->exit_status = ft_calc_exit_status(str);
	else
	{
		i = 1;
		data->exit_status = 2;
		printf("exit\nbash: exit: %s: numeric argument required\n", str);
	}
	return (i);
}


/* int	is_exit(t_data *data)
{
	char	**arr;
	int		size;
	int		i;

	arr = ft_split(data->input, 32);
	if (!arr)
		perror("malloc");
	size = ft_arrsize(arr);
	i = 0;
	if (ft_strncmp(arr[0], "exit", ft_strlen(arr[0])) == 0) // delete
	{
		i = 1;
		if (size == 2)
		{
			if (ft_isdigit_str(arr[1]))
				data->exit_status = ft_calc_exit_status(arr[1]);
			else
			{
				i = 1;
				data->exit_status = 2;
				printf("exit\nbash: exit: %s: numeric argument required\n", arr[1]);
				// ft_free_arr(arr); // exit for real
			}
		}
		else if (size > 2)
		{
			i = 0;
			data->exit_status = 1;
			printf("exit\nbash: exit: too many arguments\n"); // doesn't exit for real
		}
	}
	else
	{
		i = 0;
		// data->exit_status = 127;
		// printf("%s: command not found\n", arr[0]);
	}
	ft_free_arr(arr);
	return (i);
} */

static int	ft_calc_exit_status(char *str)
{
	int	code;

	code = ft_atoi(str) % 256;
	if (code < 0)
		code += 256;
	return (code);
}

void	exit_handler(t_data *data) // ok so far
{
	int		er_num;

	er_num = data->exit_status;
	rl_clear_history();
	if (data)
		ft_free_data(data);
	ft_putendl_fd("exit", 1); // or 1 ??
	printf("exit_status = %d\n", er_num); // delete
	exit(er_num);
}

/*
1. If user provides Exit with argument
	- exit with the specified status code
2. if Exit without argument
	- the exit status is that of the last command executed
	- If no command has been executed yet, with a defeult status - 0
Before exiting, consider cleaning up any resources that the Minishell has allocated, such as memory, file descriptors, or temporary files
*/

// res my function
/*
--- 1 ---
sh$ exitt
exitt: command not found
sh$ Error execve() // schould be only new_prompt
: No such file or directory 
--- 2 ---
sh$ exit 3.14
exit
bash: exit: 3.14: numeric argument required // schould be also exit for real
sh$ // free_data
exit // 
--- 3 ---
// my function doesn't work with exit argument out of the range 0-255
ohladkov@c4b4c6:~$ exit +2
exit
c4b4c6% echo $?
2
c4b4c6% bash   
ohladkov@c4b4c6:~$ exit -2
exit
c4b4c6% echo $?
254
--- 4 ---
--- 5 ---
--- 6 ---
--- 7 ---
*/
