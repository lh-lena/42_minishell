#include "sh.h"

// to change ->
// if (ft_strncmp(input->argv[0], "cd", 2) == 0) -> if (ft_strncmp(input->argv[0], 'cd', ft_strlen(argv[0])) == 0)
static void	check_cmd(t_data *input, char **arr)
{
	if (ft_strncmp(arr[0], "cd", ft_strlen(arr[0])) == 0)
		dir_tr(input);
	else if (ft_strncmp(arr[0], "exit", ft_strlen(arr[0])) == 0)
	{
		if (is_exit(input))
			exit_handler(input);
	}
	else if(ft_strncmp(arr[0], "env", ft_strlen(arr[0])) == 0)
		env_print(input);
	else if (ft_strncmp(arr[0], "export", ft_strlen(arr[0])) == 0)
		export(input, arr);
	else if (ft_strncmp(arr[0], "unset", ft_strlen(arr[0])) == 0)
		unset(input, arr);
	else
		execve_tr(input);
}

static void	parse_input(t_data	*input)
{
	char	**arr;

	if (input->argv != NULL)
		ft_free_arr(input->argv);
	arr = ft_split(input->input, ' ');
	if (!arr)
		perror("malloc\n");
	input->argv = arr;
	check_cmd(input, arr);
}

void	init_data(t_data *data)
{
	data->argv = NULL;
	data->exit_status = 0;
}

void	minishell(t_data *data)
{
	while (1)
	{
		data->input = readline("sh$ ");
		if (!data->input)
		{
			ft_putendl_fd("ctrl+D", 1);
			ft_free_data(data);
			exit(1);
		}
		else
		{
			create_history(data);
			parse_input(data);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	// manage_signal();
	// determines if file descriptor is associated with a terminal
	if (isatty(STDIN_FILENO) == 1)
	{
		t_data	*data;

		data = (t_data *)malloc(sizeof(t_data));
		data->envp = envp;
		data->env_lst = ft_getenv(envp);
		init_data(data);
		minishell(data);
	}
	return (0);
}
