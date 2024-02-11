/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:17:34 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/02 15:03:33 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	pwd_cmd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		data->exit_status = 0;
		ft_putendl_fd(pwd, 1);
	}
	else
		put_error(data, strerror(errno), 1);
	ft_free(&pwd);
}
