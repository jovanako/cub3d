/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:00:46 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 17:03:14 by jkovacev         ###   ########.fr       */
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


int		parse_file(int fd);
void	print_error(char *error);
int		print_error_and_return(char *error, int ret);
void	invalid_tex();
char	*get_path(char *found);
int		parse_line(char *line, t_config *config);
int		parse_north_tex(char *line, t_config *config);
int		parse_south_tex(char *line, t_config *config);
int		parse_west_tex(char *line, t_config *config);
int		parse_east_tex(char *line, t_config *config);
int		has_valid_chars(char *line);
int		array_size(char **arr);
int		in_range(int n);
int		parse_floor_color(char *line, t_config *config);
int		parse_ceiling_color(char *line, t_config *config);
#endif