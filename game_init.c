/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:10:01 by asalniko          #+#    #+#             */
/*   Updated: 2026/04/11 17:10:04 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"
#include "mlx.h"

int	close_game(t_game *game)
{
	deep_free_game(game);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
	else if (keycode == KEY_W)
		move_player(game, MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(game, -MOVE_SPEED);
	else if (keycode == KEY_A)
		strafe_player(game, -MOVE_SPEED);
	else if (keycode == KEY_D)
		strafe_player(game, MOVE_SPEED);
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_and_return("MLX init failed\n", 0));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (print_error_and_return("Window creation failed\n", 0));
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	return (1);
}

int	render_loop(t_game *game)
{
	render_frame(game);
	return (0);
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}
