/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:36:50 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/11 22:40:58 by ohladkov         ###   ########.fr       */
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
	temp =  NULL;
	while (++i < ft_arrsize(input))
	{
		if (!isvalid_var_name_str(input[i]))
		{
			put_error_arg(data, "bash: export: `", input[i], "': not a valid identifier", 1);
			break ;
		}
		else if (isvalid_export_input(input[i]))
		{
			temp = input[i];
			input[i] = expand_str(data, temp);
			if (!input[i])
				malloc_error();
			ft_free(&temp);
			env_replace_or_create_node(data->env_lst, input[i]);
		}
	}
}
