/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:45:49 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/10 22:10:53 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid_path(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*get_path(char *direction)
{
	char	*start;
	
	start = ft_strchr(direction, '.');
	if (!is_valid_path(start))
		return (invalid_tex(), NULL);
	return (start);
}

int	parse_any_path(char *line, t_config *config)
{	
	if (ft_strchr(line, 'N'))
		return (parse_north_tex(line, config));
	if (ft_strchr(line, 'S'))
		return (parse_south_tex(line, config));
	if (ft_strchr(line, 'W'))
		return (parse_west_tex(line, config));
	if (ft_strchr(line, 'E'))
		return (parse_east_tex(line, config));
	return (print_error_and_return("Path input missing\n", 0));
}
