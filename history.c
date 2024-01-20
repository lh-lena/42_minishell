/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:15 by ohladkov          #+#    #+#             */
/*   Updated: 2024/01/20 13:40:16 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh.h"

void	create_history(t_data *data)
{
	const char	*str;

	str = data->input;
	if (str)
		add_history(str);
}

// https://www.math.utah.edu/docs/info/hist_2.html
// https://stackoverflow.com/questions/38792542/readline-h-history-usage-in-c
