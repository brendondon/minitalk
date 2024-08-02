/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:44:02 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 17:44:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	action(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int	i = 0;

	(void)context;
	(void)info;
	if (sig == SIGUSR1)
		c |= 1 << i;
	if (sig == SIGUSR2)
		c |= 0 << i;
	i++;
	if (i == 8)
	{
		//kill(info->si_pid, SIGUSR2);
		write(1, &c, 1);
		i = 0;
		c = 0;
		//kill(info->si_pid, SIGUSR1);
	}

}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("pid: %d\n", getpid());
	while (1)
		pause();
	return (0);
}