/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:11:26 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/14 18:18:57 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	calculate_map_width(char **grid)
{
	int	i;
	int	len;
	int	width;

	i = 0;
	len = 0;
	width = 0;
	if (!grid)
		return (0);
	while (grid[i])
	{
		len = (int)ft_strlen(grid[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

int	has_config(t_config *config)
{
	if (config)
	{
		return (config->north.path && config->south.path
			&& config->west.path && config->east.path
			&& config->floor_set && config->ceiling_set);
	}
	print_error("Texture values missing\n");
	return (0);
}

int	normalize_map(t_map *map)
{
	char	*new_line;
	int		i;
	int		len;

	i = 0;
	while (i < map->height)
	{
		new_line = ft_calloc(map->width + 1, sizeof(char));
		if (!new_line)
			return (print_error_and_return("Malloc failed\n", 0));
		ft_memset(new_line, ' ', map->width);
		len = (int)ft_strlen(map->grid[i]);
		ft_memcpy(new_line, map->grid[i], len);
		free(map->grid[i]);
		map->grid[i] = new_line;
		i++;
	}
	return (1);
}

int	parse_empty_line(char *trimmed_line, t_parse_state *state)
{
	if (trimmed_line[0] != '\0')
		return (-1);
	if (state->map_started)
		state->map_ended = 1;
	free(trimmed_line);
	return (1);
}

int	parse_map_line(char *trimmed_line, char *line, t_game *game,
		t_parse_state *state)
{
	if (has_config(&game->config) && is_map(trimmed_line))
	{
		state->map_started = 1;
		return (parse_grid(line, &game->map));
	}
	if (has_config(&game->config) && !is_map(trimmed_line))
		return (print_error_and_return("Invalid line in map\n", 0));
	return (print_error_and_return("Configuration incomplete before map\n", 0));
}
