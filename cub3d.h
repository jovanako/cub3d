/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalniko <asalniko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:37:40 by jkovacev          #+#    #+#             */
/*   Updated: 2026/04/14 17:52:00 by asalniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define ROT_SPEED 0.1
# define MOVE_SPEED 0.1

# define FOV 60
# define FOV2 30
# define PI 3.14159265358979323846

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# include <math.h>
# include <mlx.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	char	*path;
	t_img	img;
}	t_texture;

typedef struct s_config
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	int			floor_color;
	int			ceiling_color;
	int			floor_set;
	int			ceiling_set;
}	t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	dist;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		height;
	int		start;
	int		end;
}	t_ray;

typedef struct s_game
{
	t_config	config;
	t_map		map;
	t_player	player;
	void		*mlx;
	void		*win;
	t_img		img;
}	t_game;

//init
int			init_game(t_game *game);
int			close_game(t_game *game);
int			handle_key(int keycode, t_game *game);
int			init_image(t_game *game);
void		init_ray(t_game *game, t_ray *ray, int x);
void		set_step_and_side_dist(t_game *game, t_ray *ray);
void		perform_dda(t_game *game, t_ray *ray);
void		calculate_wall_projection(t_game *game, t_ray *ray);

void		rotate_player(t_game *game, double angle);
void		move_player(t_game *game, double move);
void		strafe_player(t_game *game, double move);

//render
void		render_frame(t_game *game);
int			render_loop(t_game *game);

int			load_textures(t_game *game);
t_texture	*get_wall_texture(t_game *game, t_ray *ray);
int			validate_args(int argc, char *path);

void		calculate_wall_x(t_game *game, t_ray *ray);
void		calculate_tex_x(t_texture *tex, t_ray *ray);
void		calculate_tex_y(t_texture *tex, t_ray *ray);
void		draw_textured_line(t_game *game, int x, t_ray *ray, t_texture *tex);

//math
double		ft_abs(double n);

#endif
