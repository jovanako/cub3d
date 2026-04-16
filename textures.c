/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:23:07 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/11 21:23:09 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"
#include "mlx.h"

static int	load_texture(t_game *game, t_texture *tex)
{
	tex->img.img = mlx_xpm_file_to_image(game->mlx, tex->path,
			&tex->img.width, &tex->img.height);
	if (!tex->img.img)
		return (0);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.addr)
		return (0);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_texture(game, &game->config.north))
		return (print_error_and_return("North texture load failed\n", 0));
	if (!load_texture(game, &game->config.south))
		return (print_error_and_return("South texture load failed\n", 0));
	if (!load_texture(game, &game->config.west))
		return (print_error_and_return("West texture load failed\n", 0));
	if (!load_texture(game, &game->config.east))
		return (print_error_and_return("East texture load failed\n", 0));
	return (1);
}

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->config.east);
		return (&game->config.west);
	}
	if (ray->dir_y > 0)
		return (&game->config.south);
	return (&game->config.north);
}

void	calculate_tex_x(t_texture *tex, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)tex->img.width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->img.width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->img.width - ray->tex_x - 1;
}

void	calculate_tex_y(t_texture *tex, t_ray *ray)
{
	ray->step = 1.0 * tex->img.height / ray->height;
	ray->tex_pos = (ray->start - WIN_HEIGHT / 2 + ray->height / 2)
		* ray->step;
}
