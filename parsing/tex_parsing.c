/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:50:05 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 10:27:43 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_north_tex(char *line, t_config *config)
{
	char	*direction;
	char	*start;
	
	direction = ft_strchr(line, 'N');
	if (ft_strncmp(direction, "NO ", 3))
		return (invalid_tex(), 0);
	start = get_path(direction);
	config->north.path = ft_strdup(start);
	if (!config->north.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}

int	parse_south_tex(char *line, t_config *config)
{
	char	*direction;
	char	*start;
	
	direction = ft_strchr(line, 'S');
	if (ft_strncmp(direction, "SO ", 3))
		return (invalid_tex(), 0);
	start = get_path(direction);
	config->south.path = ft_strdup(start);
	if (!config->south.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}

int	parse_west_tex(char *line, t_config *config)
{
	char	*direction;
	char	*start;
	
	direction = ft_strchr(line, 'W');
	if (ft_strncmp(direction, "WE ", 3))
	{
		invalid_tex();
		return (0);
	}
	start = get_path(direction);
	config->west.path = ft_strdup(start);
	if (!config->west.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}

int	parse_east_tex(char *line, t_config *config)
{
	char	*direction;
	char	*start;
	
	direction = ft_strchr(line, 'E');
	if (ft_strncmp(direction, "EA ", 3))
	{
		invalid_tex();
		return (0);
	}
	start = get_path(direction);
	config->east.path = ft_strdup(start);
	if (!config->east.path)
		print_error_and_return("Malloc failed\n", 0);
	return (1);
}