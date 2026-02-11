/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:08:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/11 11:02:47 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"

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
		if (!parse_any_path(line, config))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
