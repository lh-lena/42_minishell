#include "sh.h"

void	panic(char	*s)
{
	perror(s);
	exit(1);
}

int	fork1(void)
{
	int	pid;
	pid = fork();
	if (pid == -1)
		panic("fork\n");
	return (pid);
}
