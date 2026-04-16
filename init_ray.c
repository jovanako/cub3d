/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:29:02 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/14 17:59:01 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"

static int	is_wall_or_invalid(t_map *map, int x, int y)
{
	char	cell;

	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	cell = map->grid[y][x];
	return (cell == '1' || cell == ' ');
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = ft_abs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = ft_abs(1 / ray->dir_y);
	ray->hit = 0;
}

void	set_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall_or_invalid(&game->map, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}
