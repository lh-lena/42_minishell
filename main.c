#include "sh.h"

static void	check_cmd(t_data *input)
{
	if (ft_strncmp(input->argv[0], "cd", 2) == 0)
		dir_tr(input);
	else if(ft_strncmp(input->argv[0], "env", 3) == 0)
		env_print(input);
	else if (ft_strncmp(input->argv[0], "export", 3) == 0)
		export(input);
	else
		execve_tr(input);
}
static void	parse_input(t_data	*input)
{
	char	**arr;

	arr = ft_split(input->input, ' ');
	if (!arr)
		perror("malloc\n");
	input->argv = arr;
	check_cmd(input);
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
			ft_putendl_fd("exit input", 2);
			ft_free_data(data);
			exit(1);
		}
		else
		{
			if (is_exit(data))
				exit_handler(data);
			else
			{
				create_history(data);
				parse_input(data);
			}
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