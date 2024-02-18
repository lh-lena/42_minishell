/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:17:34 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/18 16:10:09 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_dir(char *path);
static void	tohome_dir(t_data *data);
static void	toprev_dir(t_data *data);
static void	change_dir(t_data *data, char *path);

void	cd_builtin(t_data *data, char **arr)
{
	size_t	size;

	size = ft_arrsize(arr);
	data->exit_status = 0;
	if (size > 2)
		put_error(data, "bash: cd: too many arguments", 1);
	else if (size == 1)
		tohome_dir(data);
	else if (ft_strncmp(arr[1], "~", ft_strlen(arr[1])) == 0 && size == 2)
		tohome_dir(data);
	else if (ft_strncmp(arr[1], "-", ft_strlen(arr[1])) == 0 && size == 2)
		toprev_dir(data);
	else if (check_dir(arr[1]) == 0)
		put_error(data, "cd: No such file or directory", 1);
	else if (size == 2)
		change_dir(data, arr[1]);
}

static int	check_dir(char *path)
{
	DIR	*temp_dir;

	temp_dir = opendir(path);
	if (temp_dir == NULL)
	{
		return (0);
	}
	if (closedir(temp_dir) == -1)
		perror("closedir");
	return (1);
}

static void	change_dir(t_data *data, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	new_pwd = NULL;
	if (chdir(path) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			env_update_val(data->env_lst, "PWD", new_pwd);
			if (old_pwd)
				env_update_val(data->env_lst, "OLDPWD", old_pwd);
			else
				put_error(data, strerror(errno), 1);
		}
		else
			put_error(data, strerror(errno), 1);
	}
	else
		put_error(data, strerror(errno), 1);
		// put_error_arg(data, "bash: cd: ", path, strerror(errno), 1);
	ft_free(&old_pwd);
	ft_free(&new_pwd);
}

static void	tohome_dir(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = env_var_value(data->env_lst, "HOME");
	old_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		if (chdir(new_pwd) == 0)
		{
			env_update_val(data->env_lst, "PWD", new_pwd);
			if (old_pwd)
				env_update_val(data->env_lst, "OLDPWD", old_pwd);
			else
				put_error(data, strerror(errno), 1);
		}
		else
			put_error(data, strerror(errno), 1);
	}
	else
		put_error(data, "bash: cd: HOME not set", 1);
	ft_free(&old_pwd);
}

static void	toprev_dir(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = env_var_value(data->env_lst, "OLDPWD");
	new_pwd = getcwd(NULL, 0);
	if (old_pwd != NULL)
	{
		if (chdir(old_pwd) == 0)
		{
			env_update_val(data->env_lst, "PWD", old_pwd);
			if (new_pwd)
				env_update_val(data->env_lst, "OLDPWD", new_pwd);
			else
				put_error(data, strerror(errno), 1);
		}
	}
	else
		put_error(data, strerror(errno), 1);
	ft_free(&new_pwd);
}
