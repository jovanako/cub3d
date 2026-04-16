/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:07:11 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/11 21:07:13 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"
#include "mlx.h"

static int	is_walkable_cell(t_map *map, int x, int y)
{
	char	cell;

	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	cell = map->grid[y][x];
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W');
}

void	move_player(t_game *game, double move)
{
	int	new_x;
	int	new_y;

	new_x = (int)(game->player.x + game->player.dir_x * move);
	new_y = (int)(game->player.y + game->player.dir_y * move);
	if (is_walkable_cell(&game->map, new_x, (int)game->player.y))
		game->player.x += game->player.dir_x * move;
	if (is_walkable_cell(&game->map, (int)game->player.x, new_y))
		game->player.y += game->player.dir_y * move;
}

void	strafe_player(t_game *game, double move)
{
	int	new_x;
	int	new_y;

	new_x = (int)(game->player.x + game->player.plane_x * move);
	new_y = (int)(game->player.y + game->player.plane_y * move);
	if (is_walkable_cell(&game->map, new_x, (int)game->player.y))
		game->player.x += game->player.plane_x * move;
	if (is_walkable_cell(&game->map, (int)game->player.x, new_y))
		game->player.y += game->player.plane_y * move;
}
