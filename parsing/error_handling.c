/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:59:28 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 09:23:47 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
