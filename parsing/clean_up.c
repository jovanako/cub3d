/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:48:43 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 13:02:07 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"

int	rgb_cleanup(t_rgb *rgb)
{
	if (rgb)
		free(rgb);
	return (0);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free(config->north.path);
	free(config->south.path);
	free(config->west.path);
	free(config->east.path);
	free(config);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->grid)
		return ;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map);
}

void	deep_free_game(t_game *game)
{
	if (!game)
		return ;
	free_config(&game->config);
	free_map(&game->map);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	free(game);
}