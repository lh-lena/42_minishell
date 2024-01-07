#include "sh.h"

void	print_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%d = %s\n", i, arr[i]);
		i++;
	}
}

size_t	ft_arrsize(char	**arr)
{
	size_t	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}
