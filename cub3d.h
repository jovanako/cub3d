/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:37:40 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/08 15:27:54 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		*data;
	int		width;
	int		height;
}	t_texture;

/***
 * floor_color and ceiling_color represent rgb values, packed in an int as
 * 0x00RRGGBB since MLX expects it in this format
 */
typedef struct s_config
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	int			floor_color;
	int			ceiling_color;
}	t_config;

/***
 * x, y - player position
 * dir_x, dir_y - looking direction
 * plane_x, plane_y - field of view
 */	
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

typedef struct s_game
{
	t_config	config;
	t_map		map;
	t_player	player;
	void		*mlx;
	void		*win;
}	t_game;
