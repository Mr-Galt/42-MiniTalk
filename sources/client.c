/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinke <mheinke@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:30:40 by mheinke           #+#    #+#             */
/*   Updated: 2023/12/12 15:18:28 by mheinke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include <stdlib.h>

void	args_check(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("\033[31m\033[1mInvalid number of arguments\n\033[0m");
		ft_printf("\033[32m\033[1mExample:\033[0m");
		ft_printf("\033[33m./client [server PID] [message]\n\033[0m");
		exit(1);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
		{
			ft_printf("\033[31m\033[1mInvalid PID\n\033[0m");
			exit(1);
		}
	}
	if (*argv[2] == 0)
	{
		ft_printf("\033[31m\033[1mYou try to send an empty message\n\033[0m");
		exit(1);
	}
}

/**
 * @brief Sends a string to another process character by character
 *        using UNIX signals. Each character is sent as a series of bits. 
 *        For each bit, a signal is sent to the process with the given PID.
 *        SIGUSR2 is sent to represent a '1' bit, and SIGUSR1 is sent to 
 *        represent a '0' bit. The function sends 7 bits for each character,
 *		  suitable for 7-bit ASCII encoding.
 *
 * @param pid The Process ID (PID) of the receiving process.
 * @param str The string to be sent. The function sends each character
 *            of this string as a series of bits.
 * @param len The length of the string. This is used to determine when
 *            the entire string has been sent.
 */

void	send_bit(int pid, char *str, size_t len)
{
	int		shift;
	size_t	i;

	i = 0;
	while (i <= len)
	{
		shift = 0;
		while (shift < 7)
		{
			if ((str[i] >> shift) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			shift++;
			usleep(690);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	args_check(argc, argv);
	pid = ft_atoi(argv[1]);
	str = argv[2];
	send_bit(pid, str, ft_strlen(str));
	usleep(500);
}
