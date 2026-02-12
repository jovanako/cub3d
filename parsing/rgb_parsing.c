/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:00:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 20:48:45 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**get_rgb_arr(char *line, char **rgb_arr)
{
	char	*trimmed_line;
	
	trimmed_line = ft_strtrim(line + 1, " "); 
	if (!trimmed_line)
		return (NULL);
	rgb_arr = ft_split(trimmed_line, ',');
	if (!rgb_arr)
	{
		free(trimmed_line);
		return (NULL);
	}
	free(trimmed_line);
	return (rgb_arr);
}

void	assign_rgb(t_rgb *rgb, int i, int val)
{
	if (i == 0)
		rgb->r = val;
	else if (i == 1)
		rgb->g = val;
	else if (i == 2)
		rgb->b = val;
}

int	get_rgb_val(char *line, t_rgb *rgb)
{
	char	**rgb_arr;
	char	*temp;
	int		i;
	int		val;

	rgb_arr = NULL;
	i = 0;
	rgb_arr = get_rgb_arr(line, rgb_arr);
	if (!rgb_arr)
		return (0);
	if (array_size(rgb_arr) != 3)
	{
		rgb_arr_cleanup(rgb_arr);
		return(print_error_and_return("Invalid input for color\n", 0));
	}
	while (i < 3)
	{
		temp = ft_strtrim(rgb_arr[i], " ");
		if (!temp)
			return (0);
		val = ft_atoi(temp);
		assign_rgb(rgb, i, val);
		free(temp);
		i++;
	}
	rgb_arr_cleanup(rgb_arr);
	return (1);
}
