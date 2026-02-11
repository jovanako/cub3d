/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:00:46 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/11 09:57:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

int		parse_file(int fd);
void	print_error(char *error);
int		print_error_and_return(char *error, int ret);
void	invalid_tex();
char	*get_path(char *found);
int		parse_any_path(char *line, t_config *config);
int		parse_north_tex(char *line, t_config *config);
int		parse_south_tex(char *line, t_config *config);
int		parse_west_tex(char *line, t_config *config);
int		parse_east_tex(char *line, t_config *config);
#endif