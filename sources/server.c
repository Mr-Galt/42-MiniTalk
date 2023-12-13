/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinke <mheinke@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:31:08 by mheinke           #+#    #+#             */
/*   Updated: 2023/12/13 15:51:54 by mheinke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

/**
 * @brief Handles signal-based character assembly for server-side communication.
 *
 * This function is invoked when SIGUSR1 signals are received. It reconstructs
 * characters from individual bits sent by the client. Each bit is assembled
 * into a byte, and once all 8 bits are received, the byte is interpreted as
 * a character and printed. After printing the character, it resets the bit
 * counter and character accumulator, and sends a SIGUSR2 signal back to the
 * client as an acknowledgment.
 *
 * @param signal The signal received (SIGUSR1).
 * @param info Unused parameter
 * @param s Unused parameter
 */

void	bit_handler(int signal, siginfo_t *info, void *s)
{
	static int	bit;
	static int	i;

	(void)info;
	(void)s;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("\033[32m\n");
	ft_printf("███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗  ██╗\n");
	ft_printf("████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝\n");
	ft_printf("██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝ \n");
	ft_printf("██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗ \n");
	ft_printf("██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗\n");
	ft_printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
	ft_printf("\n");
	ft_printf("\tby Martin\t\tServer PID: %d\n", getpid());
	ft_printf("\033[0m\n\033[4mWaiting for Incoming Messages:\n\033[0m");
	sig.sa_sigaction = bit_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	while (1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
