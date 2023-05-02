/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afgoncal <afgoncal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:00:12 by afgoncal          #+#    #+#             */
/*   Updated: 2023/05/02 16:19:32 by afgoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	c = 0;

	(void)context;
	if (sig == SIGUSR1)
		c |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (c == 0)
			kill(info->si_pid, SIGUSR1);
		else
			ft_printf("%c", c);
		bit_count = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	act;

	if (ac != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		(void)av;
		return (0);
	}
	act.sa_sigaction = ft_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	pid = getpid();
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	ft_printf ("%d\n", pid);
	while (1)
		sleep(1);
}
