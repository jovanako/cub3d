/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:28:25 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:35:01 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEX_H
# define TEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub3d.h"
#include "libft.h"
#include "parse.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Parse tex
char	*get_path(char *line);
int		parse_north_tex(char *line, t_config *config);
int		parse_south_tex(char *line, t_config *config);
int		parse_west_tex(char *line, t_config *config);
int		parse_east_tex(char *line, t_config *config);

// Parse color
int		get_rgb_val(char *line, t_rgb *rgb);
int		parse_floor_color(char *line, t_config *config);
int		parse_ceiling_color(char *line, t_config *config);
void	rgb_arr_cleanup(char **rgb_arr);
int		clean_and_return(char **rgb_arr);
#endif