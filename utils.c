/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbart <sbart@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:44:17 by sbart             #+#    #+#             */
/*   Updated: 2022/03/13 20:28:08 by sbart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_error(int tag)
{
	if (tag == 0)
		write(1, "Incorrect number of arguments.\n", 32);
	else if (tag == 1)
		write(1, "Pipe creating error\n", 20);
	else if (tag == 2)
		write(1, "Fork creating error\n", 20);
	else if (tag == 3)
		write(1, "The file cannot be opened\n", 26);
	else if (tag == 4)
		write(1, "Command not found\n", 18);
	exit(1);
}

