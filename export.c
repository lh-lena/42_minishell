/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:36:50 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 15:53:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh.h"

// input[0] input[1] input[1]
// export   var=val  var=val
void	export(t_data *data, char **input)
{
	size_t	i;
	char	*temp;

	i = 0;
	data->exit_status = 0;
	while (++i < ft_arrsize(input))
	{
		if (is_quotes(input[i]) == -1)
		{
			print_error(data, "bash: export: Quotes are not correctly closed", 5);
		}
		else if (isvalid_export_input(input[i]))
		{
			temp = export_execution(data, input[i]);
			if (temp != NULL)
			{
				free(input[i]);
				input[i] = temp;
			}
			env_replace_or_create_node(data->env_lst, input[i]);
		}
		else if (!isvalid_export_input(input[i]))
			print_error_arg(data, "bash: export: `", input[i],"': not a valid identifier", 1);
	}
}

// return 5 - if quotes don't close
char	*export_execution(t_data *data, char *input)
{
	char	*temp_new;

	temp_new = NULL;
	if (is_quotes(input) == 1 || is_quotes(input) == 2)
	{
		temp_new = edit_str(data->env_lst, input); // malloc
		if (!temp_new)
			perror("malloc export_execution");
	}
	else if (ft_strchr(input, '$'))
	{
		temp_new = get_replaced_str(data->env_lst, input); // malloc
		if (!temp_new)
			perror("malloc export_execution");
	}
	return (temp_new);
}
