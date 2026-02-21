/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:59:28 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/20 19:22:52 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	print_error(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
}

int	print_error_and_return(char *error, int ret)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	return (ret);
}

void	print_invalid_char(char c)
{
	print_error("Invalid map character: ");
	ft_putchar_fd('\'', 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\'', 2);
	write(2, "\n", 1);
}