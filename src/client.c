/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afgoncal <afgoncal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:00:02 by afgoncal          #+#    #+#             */
/*   Updated: 2023/05/02 17:10:58 by afgoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	ft_send_bits(int pid, char c)
{
	int	bit_count;

	bit_count = 0;
	while (bit_count < 8)
	{
		if (c & (1 << bit_count))
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		bit_count++;
		usleep (100);
	}
}

void	server_says_hello(int sig)
{
	(void)sig;
	ft_printf("Message received");
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	signal(SIGUSR1, server_says_hello);
	pid = ft_atoi(argv[1]);
	i = 0;
	if (argc != 3)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		return (0);
	}
	while (argv[2][i])
	{
		ft_send_bits (pid, argv[2][i]);
		i++;
	}
	ft_send_bits(pid, 0);
}
