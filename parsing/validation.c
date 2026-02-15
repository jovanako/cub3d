/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:37:26 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/13 10:27:35 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	array_size(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	in_range(int n)
{
	return (n >= 0 && n <= 255);
}

int	has_valid_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 'F' && line[i] != 'C' && line[i] != ' '
			&& line[i] != ',' && !ft_isdigit(line[i]))
		{
			print_error("Invalid input for color\n");	
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_path(char *s)
{
	return (!ft_strncmp(s, "NO", 2) || !ft_strncmp(s, "SO", 2)
		|| !ft_strncmp(s, "WE", 2) || !ft_strncmp(s, "EA", 2));
}

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