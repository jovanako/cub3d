/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:00:46 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 15:11:42 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_grid
{
	char	*line;
}	t_grid;

t_game	*parse_file(int fd, t_game *game);

// Error handling
void	print_error(char *error);
int		print_error_and_return(char *error, int ret);
void	invalid_tex();

// Texture parsing
char	*get_path(char *found);
int		is_path(char *s);
char	*skip_leading_ws(char *s);
int		parse_north_tex(char *line, t_config *config);
int		parse_south_tex(char *line, t_config *config);
int		parse_west_tex(char *line, t_config *config);
int		parse_east_tex(char *line, t_config *config);

// Color parsing
int		has_valid_chars(char *line);
int		array_size(char **arr);
int		in_range(int n);
int		get_rgb_val(char *line, t_rgb *rgb);
int		parse_floor_color(char *line, t_config *config);
int		parse_ceiling_color(char *line, t_config *config);
int		rgb_cleanup(t_rgb *rgb);

// Map parsing
int		has_config(t_config *config);
int 	is_map(char *line);
int		calculate_map_height(char *arg, t_game *game);
int		parse_grid(char *line, t_map *map);
void	free_config(t_config *config);
void	free_map(t_map *map);
void	deep_free_game(t_game *game);
#endif