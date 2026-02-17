/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:15:12 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 10:15:29 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_config(t_config *config)
{
	if (config)
	{
		return (config->north.path && config->south.path
				&& config->west.path && config->east.path
				&& config->floor_color &&config->ceiling_color);
	}
	print_error("Texture values missing\n");
	return (0);
}

int is_map(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i])
	{
		if ((line[i] == 'N' && line[i + 1] == 'O')
			|| (line[i] == 'S' && line[i + 1] == 'O')
			|| (line[i] == 'W' && line[i + 1] == 'E')
			|| (line[i] == 'E' && line[i + 1] == 'A')
			|| line[i] == 'F' || line[i] == 'C')
			return (0);
		if (line[i] == '1')
			return (1);
		return (0);
	}
	return (0);
}