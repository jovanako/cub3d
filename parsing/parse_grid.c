/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:14:02 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/21 14:53:48 by jkovacev         ###   ########.fr       */
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

void	clean_up_grid_copy(char **grid_copy)
{
	int	i;

	i = 0;
	if (!grid_copy)
		return ;
	while (grid_copy[i])
	{
		free(grid_copy[i]);
		i++;
	}
	free(grid_copy);
}