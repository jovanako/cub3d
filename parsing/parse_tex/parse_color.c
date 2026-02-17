/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:20:13 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:29:53 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"

static int	rgb_cleanup(t_rgb *rgb)
{
	if (rgb)
		free(rgb);
	return (0);
}

static int	in_range(int n)
{
	return (n >= 0 && n <= 255);
}

static int	rgb_valid_chars(char *line)
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

int	parse_floor_color(char *line, t_config *config)
{
	t_rgb	*rgb;

	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		return (print_error_and_return("Malloc failed\n", 0));
	if (!rgb_valid_chars(line))
		return (rgb_cleanup(rgb));
	if (!get_rgb_val(line, rgb))
		return (rgb_cleanup(rgb));
	if (!in_range(rgb->r) || !in_range(rgb->g) || !in_range(rgb->b))
	{
		print_error("RGB value out of range\n");
		return (rgb_cleanup(rgb));
	}
	config->floor_color = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	free(rgb);
	return (1);
}

int	parse_ceiling_color(char *line, t_config *config)
{
	t_rgb	*rgb;

	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		return (print_error_and_return("Malloc failed\n", 0));
	if (!rgb_valid_chars(line))
		return (rgb_cleanup(rgb));
	if (!get_rgb_val(line, rgb))
		return (rgb_cleanup(rgb));
	if (!in_range(rgb->r) || !in_range(rgb->g) || !in_range(rgb->b))
	{
		print_error("RGB value out of range\n");
		return (rgb_cleanup(rgb));
	}
	config->ceiling_color = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	free(rgb);
	return (1);
}
