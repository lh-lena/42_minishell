/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:30:01 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/17 16:43:10 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handle);
}

void	sig_handle(int sig_num)
{
	(void)sig_num;
	g_sig_status = 1;
	write(1, "^C\n", 2);
	ioctl(0, TIOCSTI, "\n");
}

void	manage_signal(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &sig_handle_child;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, 0) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		perror("sigaction");
}

void	sig_handle_child(int sig_num)
{
	(void)sig_num;
	g_sig_status = 1;
}

void	signal_ignr(void)
{
	signal(SIGINT, SIG_IGN);
}
