/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:08:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 18:07:58 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"

// TEST function
// void	print_config_elements(t_config *config)
// {
// 	printf("---Config---\n");
// 	printf("north path: %s\n", config->north.path);
// 	printf("south path: %s\n", config->south.path);
// 	printf("east path: %s\n", config->east.path);
// 	printf("west path: %s\n", config->west.path);
// 	printf("floor color: %#x\n", config->floor_color);
// 	printf("ceiling color: %#x\n", config->ceiling_color);
// }

int	parse_file(int fd)
{
	char		*line;
	t_config	*config;
	
	config = malloc(sizeof(t_config));
	if (!config)
		print_error_and_return("Malloc failed\n", 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, config))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	// TEST
	// print_config_elements(config);
	return (1);
}
