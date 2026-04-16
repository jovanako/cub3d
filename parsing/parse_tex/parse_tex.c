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
	if (config->north.path)
		return (print_error_and_return("Duplicate north texture\n", 0));
	config->north.path = get_path(line);
	if (!config->north.path)
		return (0);
	return (1);
}

int	parse_south_tex(char *line, t_config *config)
{
	if (config->south.path)
		return (print_error_and_return("Duplicate south texture\n", 0));
	config->south.path = get_path(line);
	if (!config->south.path)
		return (0);
	return (1);
}

int	parse_west_tex(char *line, t_config *config)
{
	if (config->west.path)
		return (print_error_and_return("Duplicate west texture\n", 0));
	config->west.path = get_path(line);
	if (!config->west.path)
		return (0);
	return (1);
}

int	parse_east_tex(char *line, t_config *config)
{
	if (config->east.path)
		return (print_error_and_return("Duplicate east texture\n", 0));
	config->east.path = get_path(line);
	if (!config->east.path)
		return (0);
	return (1);
}
