#include "sh.h"

int	is_exit(char *input)
{
	char	*str;

	str = input;
	if (ft_strncmp(str, "exit", 4) == 0 && (ft_isspace(str[4]) || str[4] == '\0'))
		return (1);
	return (0);
}

void	exit_handler(void) // ok so far
{
	int		er_num;

	er_num = errno;
	clear_history();
	ft_putendl_fd("exit", 2); // or 1 ??
	exit(er_num);
}
