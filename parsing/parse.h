/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:00:46 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/21 14:53:59 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

int		parse_tex(char *line, t_config *config);
int		parse_color(char *line, t_config *config);
t_game	*parse_file(int fd, t_game *game);
char	*skip_leading_ws(char *s);
void	print_error(char *error);
int		print_error_and_return(char *error, int ret);
void	print_invalid_char(char c);
int 	is_map(char *line);
int		is_path(char *s);
int		parse_grid(char *line, t_map *map);
void	clean_up_grid_copy(char **grid_copy);
int		validate_map(t_map *map, t_player *player);
void	deep_free_game(t_game *game);
void	set_player(t_game *game);
#endif