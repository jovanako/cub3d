/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:53:46 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/14 17:59:17 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h" 

void	calculate_wall_projection(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->dist = ray->side_x - ray->delta_x;
	else
		ray->dist = ray->side_y - ray->delta_y;
	if (ray->dist <= 0)
		ray->dist = 0.1;
	ray->height = (int)(WIN_HEIGHT / ray->dist);
	ray->start = -ray->height / 2 + WIN_HEIGHT / 2;
	ray->end = ray->height / 2 + WIN_HEIGHT / 2;
	(void)game;
}

void	calculate_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
