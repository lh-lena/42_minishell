/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:53:45 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/08 10:46:04 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	execute(char **cmd, char *envp[])
{
	char	*path;
	char	**dir;
	int		res;
	int		i;

	if (access(cmd[0], F_OK) == 0)
		return (execve(cmd[0], cmd, envp));
	dir = get_path(envp);
	if (!dir)
		return (-1);
	i = 0;
	while (dir[i])
	{
		path = ft_strcat(dir[i], cmd[0]);
		res = execve(path, cmd, envp);
		free(path);
		i++;
	}
	ft_free_arr(dir);
	return (res);
}
