/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinke <mheinke@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:31:08 by mheinke           #+#    #+#             */
/*   Updated: 2023/12/12 15:12:50 by mheinke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

/**
 * @brief Handles the reception of bits for constructing a character. 
 *        This function is typically called when a signal is received,
 *        indicating a bit of a character being transmitted. It accumulates
 *        these bits to reconstruct the full character. Once a complete
 *		  character (7 bits) is formed, it prints the character.
 *        If the character is a null terminator (0),
 *        it also prints a newline for readability.
 *
 * @param bit The least significant bit of the received signal.
 *            Should be 0 or 1.
 */

void	bit_handler(int bit)
{
	t_globalmessage	message;

	message.character += ((bit & 1) << message.index);
	message.index++;
	if (message.index == 7)
	{
		ft_printf("%c", message.character);
		if (!message.character)
			ft_printf("\n");
		message.character = 0;
		message.index = 0;
	}
}

int	main(void)
{
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
	while (1)
	{
		signal(SIGUSR2, bit_handler);
		signal(SIGUSR1, bit_handler);
		pause();
	}
	return (0);
}
