/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:17:14 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 20:20:56 by jkovacev         ###   ########.fr       */
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

static int	count_current_height(char **grid)
{
	int	count;

	count = 0;
	while (grid[count])
		count++;
	return count;
}

int	parse_grid(char *line, t_map *map)
{
	int		row;
	char	*clean_line;

	row = count_current_height(map->grid);
	clean_line = ft_strtrim(line, "\n");
	if (!clean_line)
		return (0);
	map->grid[row] = clean_line;
	return (1);
}