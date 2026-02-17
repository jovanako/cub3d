/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:16:57 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:33:27 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "mlx.h"

static void	cleanup_config(t_config *config)
{
	if (!config)
		return ;
	free(config->north.path);
	free(config->south.path);
	free(config->west.path);
	free(config->east.path);
}

static void	cleanup_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (!map->grid)
		return ;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

void	deep_free_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_config(&game->config);
	cleanup_map(&game->map);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	free(game);
}