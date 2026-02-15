/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:17:14 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 15:24:20 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	calculate_map_height(char *arg, t_game *game)
{
	int		fd;
	int		count;
	char	*line;
	
	count = 0;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_error_and_return("Open failed\n", 0));
	line = get_next_line(fd);
	while(line)
	{
		if (is_map(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->map.height = count;
	game->map.grid = ft_calloc((game->map.height + 1), sizeof(char *));
	if (!game->map.grid)
		return (print_error_and_return("Malloc failed\n", 0));
	return (1);
}

static int	count_grid_rows(char **grid)
{
	int	count;

	count = 0;
	while (grid[count])
		count++;
	return count;
}

int	parse_grid(char *line, t_map *map)
{
	int		rows;
	char	*clean_line;

	rows = count_grid_rows(map->grid);
	clean_line = ft_strtrim(line, "\n");
	if (!clean_line)
		return (0);
	map->grid[rows] = clean_line;
	// printf("grid[%d]: [%s]\n", rows, map->grid[rows]);
	return (1);
}