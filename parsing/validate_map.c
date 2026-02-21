/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:32:01 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/21 15:24:26 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	one_player_check(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'W' || map->grid[i][j] == 'E')
				count++;
			j++;
		}
		i++;		
	}
	if (count != 1)
		return (print_error_and_return("Map has more than one player\n", 0));
	return (1);
}

static int	map_valid_chars(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1'
				&& map->grid[i][j] != ' ' && map->grid[i][j] != 'N'
				&& map->grid[i][j] != 'S' && map->grid[i][j] != 'E'
				&& map->grid[i][j] != 'W')
			{
				print_invalid_char(map->grid[i][j]);
				return (0);				
			}
			j++;
		}
		i++;		
	}
	return (1);
}

static bool	copy_grid(t_map *map, char **grid_copy)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		grid_copy[i] = ft_strdup(map->grid[i]);
		if (!grid_copy[i])
		{
			clean_up_grid_copy(grid_copy);
			return (print_error("Malloc failed\n"), false);
		}
		i++;
	}
	return (true);
}

static bool	map_closure_check(t_map *map, int y, int x, char **grid_copy)
{
	if (y < 0 || x < 0 || y > map->height - 1
		|| x > map->width - 1 || grid_copy[y][x] == ' ' 
		|| grid_copy[y][x] == '\0')
	{
		print_error("Invalid map\n");
		return (false);	
	}
	if (grid_copy[y][x] == 'x' || grid_copy[y][x] == '1')
		return (true);
	grid_copy[y][x] = 'x';
	return (map_closure_check(map, y, x + 1, grid_copy)
			&& map_closure_check(map, y, x - 1, grid_copy)
			&& map_closure_check(map, y + 1, x, grid_copy)
			&& map_closure_check(map, y - 1, x, grid_copy));
}

int	validate_map(t_map *map, t_player *player)
{
	char	**grid_copy;
	int		x;
	int		y;

	x = (int)(player->x - 0.5);
	y = (int)(player->y - 0.5);
	grid_copy = ft_calloc((map->height + 1), sizeof(char *));
	if (!grid_copy)
		return (print_error_and_return("Malloc failed\n", 0));
	copy_grid(map, grid_copy);
	if (!grid_copy)
		return (0);
	if (!one_player_check(map))
		return (clean_up_grid_copy(grid_copy), 0);
	if (!map_valid_chars(map))
		return (clean_up_grid_copy(grid_copy), 0);
	if (!map_closure_check(map, y, x, grid_copy))
		return (clean_up_grid_copy(grid_copy), 0);
	clean_up_grid_copy(grid_copy);
	return (1);
}
