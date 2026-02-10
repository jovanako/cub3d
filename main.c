/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:47:23 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/10 22:00:50 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int argc, char *argv[])
{
	int fd;
	
	if (argc != 2)
		return (print_error_and_return("Invalid number of arguments\n", 1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (print_error_and_return("Open failed\n", 1));
	if (!parse_file(fd))
		return (1);
	return (0);
}