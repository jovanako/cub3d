/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:32:01 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 10:05:13 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_invalid_char(char c)
{
	print_error("Invalid map character: ");
	ft_putchar_fd('\'', 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\'', 2);
	write(2, "\n", 1);
}

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

int	map_validation(t_map *map)
{
	if (!one_player_check(map))
		return (0);
	if (!map_valid_chars(map))
		return (0);
	return (1);
}