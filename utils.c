/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:26:15 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/14 18:35:57 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"

static int	is_cub_file(char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5)
		return (0);
	return (!ft_strncmp(path + len - 4, ".cub", 5));
}

double	ft_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	validate_args(int argc, char *path)
{
	if (argc != 2)
		return (print_error_and_return("Invalid number of arguments\n", 0));
	if (!is_cub_file(path))
		return (print_error_and_return("Map must have a .cub extension\n", 0));
	return (1);
}
