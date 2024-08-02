/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:36:54 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 17:36:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
int trigger()
{
	static int i = 0;
	return i;
}

void	send_msg(pid_t sv_pid, char *msg, int trigger)
{
	unsigned char	c;
	int				bits;

	(void)trigger;
	while (*msg)
	{
		c = *msg++;
		bits = 8;
		while (bits--)
		{
			if (c & 0b10000000)
				kill(sv_pid, SIGUSR1);
			else
				kill(sv_pid, SIGUSR2);
			usleep(50);
			c <<= 1;
		}
	}
}

void	action(int sig, siginfo_t *info, void *context)
{
	int *i;

	i = 0;
	*i = trigger();
	(void)context;
	(void)info;
	if(sig==SIGUSR2)
		*i = SIGUSR2;
	if(sig==SIGUSR1)
		*i = SIGUSR1;

}



int	main(int ac, char **av)
{
	int		pid;
	char	*str;
	struct sigaction	sa;

	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
	{
		write(1, "Numero de argumentos invalido\n", 30);
		return (1);
	}
	pid = atoi(av[1]);
	str = av[2];
	printf("pid: %d\n", getpid());
	send_msg(pid, str, trigger());
	send_msg(pid, "\n", trigger());
	return (0);
}