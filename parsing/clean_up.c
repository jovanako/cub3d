/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:48:43 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 20:19:12 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rgb_cleanup(t_rgb *rgb)
{
	if (rgb)
		free(rgb);
	return (0);
}

void	rgb_arr_cleanup(char **rgb_arr)
{
	int	i;

	i = 0;
	if (!rgb_arr)
		return ;
	while (rgb_arr[i])
	{
		free(rgb_arr[i]);
		i++;
	}
	free(rgb_arr);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free(config->north.path);
	free(config->south.path);
	free(config->west.path);
	free(config->east.path);
	free(config);
}