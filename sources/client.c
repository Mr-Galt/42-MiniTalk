/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinke <mheinke@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:30:40 by mheinke           #+#    #+#             */
/*   Updated: 2023/12/13 16:01:34 by mheinke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

/**
 * @brief Validates command line arguments for the client program.
 *
 * Checks the command line arguments passed to the client for correctness.
 * It ensures the correct number of arguments, verifies if the server PID
 * is only digits (and less than 32 digits long), and confirms the message
 * is not empty. If any condition fails, it prints an error message in
 * colored and bold text, then exits the program.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 */

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
		if (!ft_isdigit(argv[1][i++]) || ft_strlen(argv[1]) > 18)
		{
			ft_printf("\033[31m\033[1mPID Error\n\033[0m");
			ft_printf("\033[31m\033[1mJust input a max 18 digits\n\033[0m");
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
 * @brief Confirms the reception of a character from the client.
 *
 * This function is a signal handler that prints a confirmation message when
 * either SIGUSR1 or SIGUSR2 is received. It uses ANSI escape codes to color
 * the output green. The function handles both signals identically, printing
 * a message indicating that a character was successfully received.
 *
 * @param signal The signal number received (SIGUSR1 or SIGUSR2).
 */

static void	confirm(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("\033[0;32mChar received!\033[0;32m\n", 1);
	else
		ft_printf("\033[0;32mChar received!\033[0;32m\n", 1);
}

/**
 * @brief Sends a character as a series of bits to the specified PID.
 *
 * This function sends each bit of the given character to the process
 * identified by 'pid', using signals. It iterates through each of the 8 
 * bits of 'character', sending SIGUSR1 for a '1' bit and SIGUSR2 for a '0' 
 * bit. The function introduces a brief pause between sending each bit to
 * ensure the receiving process can handle the incoming signals properly.
 *
 * @param pid The process ID to which the signals are sent.
 * @param character The character to send as a series of bits.
 */

void	send_bits(int pid, char character)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((character & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;

	i = 0;
	args_check(argc, argv);
	pid = ft_atoi(argv[1]);
	while (argv[2][i] != '\0')
	{
		signal(SIGUSR1, confirm);
		signal(SIGUSR2, confirm);
		send_bits(pid, argv[2][i]);
		i++;
	}
	send_bits(pid, '\n');
	usleep(500);
}
