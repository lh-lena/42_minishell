#include "sh.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	num = 0;
	if (n < 0)
	{
		num = -(n % 10);
		n = -(n / 10);
		write(fd, "-", 1);
	}
	else
	{
		num = n % 10;
		n = n / 10;
	}
	if (n > 0)
	{
		ft_putnbr_fd(n, fd);
	}
	num += 48;
	write(fd, &num, 1);
}
