/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:00:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/04/16 18:24:48 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"

static int	array_size(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

static char	**get_rgb_arr(char *line, char **rgb_arr)
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

static void	assign_rgb(t_rgb *rgb, int i, int val)
{
	if (i == 0)
		rgb->r = val;
	else if (i == 1)
		rgb->g = val;
	else if (i == 2)
		rgb->b = val;
}

static int	parse_rgb_item(char **rgb_arr, t_rgb *rgb, int i)
{
	char	*temp;
	int		val;

	temp = ft_strtrim(rgb_arr[i], " ");
	if (!temp)
		return (0);
	val = ft_atoi(temp);
	assign_rgb(rgb, i, val);
	free(temp);
	return (1);
}

int	get_rgb_val(char *line, t_rgb *rgb)
{
	char	**rgb_arr;
	int		i;

	rgb_arr = NULL;
	i = 0;
	rgb_arr = get_rgb_arr(line, rgb_arr);
	if (!rgb_arr)
		return (0);
	if (array_size(rgb_arr) != 3)
		return (clean_and_return(rgb_arr));
	while (i < 3)
	{
		if (!parse_rgb_item(rgb_arr, rgb, i))
		{
			rgb_arr_cleanup(rgb_arr);
			return (0);
		}
		i++;
	}
	rgb_arr_cleanup(rgb_arr);
	return (1);
}
