/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:20:13 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 18:01:04 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_rgb_val(char *line, t_rgb *rgb)
{
	char	*trimmed_line;
	char	**rgb_val_arr;
	char	*temp;
	int		i;
	int		val;

	i = 0;
	trimmed_line = ft_strtrim(line + 1, " "); 
	if (!trimmed_line) // add error handling to libft
		return(0);
	rgb_val_arr = ft_split(trimmed_line, ','); // error handling
	if (array_size(rgb_val_arr) != 3)
		return(print_error_and_return("Invalid input for color\n", 0));
	while (i < 3)
	{
		temp = ft_strtrim(rgb_val_arr[i], " ");
		if (!temp)
			return (0); // error handling
		val = ft_atoi(temp);
		if (i == 0)
			rgb->r = val;
		else if (i == 1)
			rgb->g = val;
		else if (i == 2)
			rgb->b = val;
		free(temp);
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
	if (!has_valid_chars(line))
		return (0);
	if (!get_rgb_val(line, rgb))
		return (0);
	if (!in_range(rgb->r) || !in_range(rgb->g) || !in_range(rgb->b))
		return (print_error_and_return("RGB value out of range\n", 0));
	config->floor_color = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	return (1);
}

int	parse_ceiling_color(char *line, t_config *config)
{
	t_rgb	*rgb;

	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		return (print_error_and_return("Malloc failed\n", 0));
	if (!has_valid_chars(line))
		return (0);
	if (!get_rgb_val(line, rgb))
		return (0);
	if (!in_range(rgb->r) || !in_range(rgb->g) || !in_range(rgb->b))
		return (print_error_and_return("RGB value out of range\n", 0));
	config->ceiling_color = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	return (1);
}