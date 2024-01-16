#include "sh.h"

void    put_error(t_data *data, char *msg, int er_num)
{
    data->exit_status = er_num;

    ft_putendl_fd(msg, 2);
}