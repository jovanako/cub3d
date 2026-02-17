/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:14:02 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:33:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	count_current_height(char **grid)
{
	int	count;

	count = 0;
	while (grid[count])
		count++;
	return count;
}

int	parse_grid(char *line, t_map *map)
{
	int		row;
	char	*clean_line;

	row = count_current_height(map->grid);
	clean_line = ft_strtrim(line, "\n");
	if (!clean_line)
		return (0);
	map->grid[row] = clean_line;
	return (1);
}

