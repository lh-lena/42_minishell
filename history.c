// https://www.math.utah.edu/docs/info/hist_2.html
// https://stackoverflow.com/questions/38792542/readline-h-history-usage-in-c

#include "sh.h"

void	create_history(t_data *data)
{
	const char	*str;

	str = data->input;
	if (str)
		add_history(str);
}
