/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:18:08 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/11 17:18:10 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"
#include "mlx.h"

int	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (print_error_and_return("Image creation failed\n", 0));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		return (print_error_and_return("Image address failed\n", 0));
	return (1);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(&game->img, x, y, game->config.ceiling_color);
			else
				put_pixel(&game->img, x, y, game->config.floor_color);
			x++;
		}
		y++;
	}
}

void	draw_textured_line(t_game *game, int x, t_ray *ray, t_texture *tex)
{
	int	y;
	int	color;

	y = ray->start;
	if (y < 0)
		y = 0;
	if (ray->end >= WIN_HEIGHT)
		ray->end = WIN_HEIGHT - 1;
	while (y <= ray->end)
	{
		ray->tex_y = (int)ray->tex_pos;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		if (ray->tex_y >= tex->img.height)
			ray->tex_y = tex->img.height - 1;
		color = ((int *)tex->img.addr)[ray->tex_y * (tex->img.line_len / 4)
			+ ray->tex_x];
		put_pixel(&game->img, x, y, color);
		ray->tex_pos += ray->step;
		y++;
	}
}

void	render_frame(t_game *game)
{
	t_ray		ray;
	t_texture	*tex;
	int			x;

	draw_background(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		set_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calculate_wall_projection(game, &ray);
		calculate_wall_x(game, &ray);
		tex = get_wall_texture(game, &ray);
		calculate_tex_x(tex, &ray);
		calculate_tex_y(tex, &ray);
		draw_textured_line(game, x, &ray, tex);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
