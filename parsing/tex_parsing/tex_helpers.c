/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:27:32 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 09:57:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"

int	is_valid_path(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
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

int	clean_and_return(char **rgb_arr)
{
	rgb_arr_cleanup(rgb_arr);
	return(print_error_and_return("Invalid input for color\n", 0));
}
