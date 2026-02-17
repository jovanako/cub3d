/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:00:46 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 10:20:58 by jkovacev         ###   ########.fr       */
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

t_game	*parse_file(int fd, t_game *game);
char	*skip_leading_ws(char *s);
void	print_error(char *error);
int		print_error_and_return(char *error, int ret);
int		has_config(t_config *config);
int 	is_map(char *line);
int		calculate_map_height(char *arg, t_game *game);
int		calculate_map_width(char **grid);
int		parse_grid(char *line, t_map *map);
int		map_validation(t_map *map);
void	deep_free_game(t_game *game);
void	set_player(t_game *game);
#endif