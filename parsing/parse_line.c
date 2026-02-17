/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:37:26 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:40:16 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "parse_tex/tex.h"

int	is_path(char *s)
{
	char	*start;

	start = skip_leading_ws(s);
	return (!ft_strncmp(start, "NO", 2) || !ft_strncmp(start, "SO", 2)
		|| !ft_strncmp(start, "WE", 2) || !ft_strncmp(start, "EA", 2));
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

char	*skip_leading_ws(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

int	parse_tex(char *line, t_config *config)
{
	char	*start;

	start = skip_leading_ws(line);
	if (!ft_strncmp(start, "NO", 2))
		return (parse_north_tex(start, config));
	if (!ft_strncmp(start, "SO", 2))
		return (parse_south_tex(start, config));
	if (!ft_strncmp(start, "WE", 2))
		return (parse_west_tex(start, config));
	if (!ft_strncmp(start, "EA", 2))
		return (parse_east_tex(start, config));
	return (0);
}
int	parse_color(char *line, t_config *config)
{
	char	*start;

	start = skip_leading_ws(line);
	if (start[0] == 'F')
		return (parse_floor_color(start, config));
	if (start[0] == 'C')
		return (parse_ceiling_color(start, config));
	return (0);
}
