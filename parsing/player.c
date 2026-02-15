/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:24:55 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 22:30:14 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_player_dir(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
	else if (c == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	else if (c == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	else if (c == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
}

void	set_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while ((int)y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y] && game->map.grid[y][x])
		{
			if (ft_isalpha(game->map.grid[y][x]))
			{
				game->player.x = (double)x + 0.5;
				game->player.y = (double)y + 0.5;
				set_player_dir(&game->player, game->map.grid[y][x]);
				game->player.plane_x = -game->player.dir_y * 0.66;
				game->player.plane_y = game->player.dir_x * 0.66;
				return ;
			}
			x++;
		}
		y++;
	}
}
