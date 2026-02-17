/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:50:05 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:30:19 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"

int	parse_north_tex(char *line, t_config *config)
{
	config->north.path = get_path(line);
	if (!config->north.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}

int	parse_south_tex(char *line, t_config *config)
{
	config->south.path = get_path(line);
	if (!config->south.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}

int	parse_west_tex(char *line, t_config *config)
{
	config->west.path = get_path(line);
	if (!config->west.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}

int	parse_east_tex(char *line, t_config *config)
{
	config->east.path = get_path(line);
	if (!config->east.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}