/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:08:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 21:21:45 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"

// TEST function
// void	print_config_elements(t_config *config)
// {
// 	printf("---Config---\n");
// 	printf("north path: %s\n", config->north.path);
// 	printf("south path: %s\n", config->south.path);
// 	printf("east path: %s\n", config->east.path);
// 	printf("west path: %s\n", config->west.path);
// 	printf("floor color: %#x\n", config->floor_color);
// 	printf("ceiling color: %#x\n", config->ceiling_color);
// }

static int	parse_tex(char *line, t_config *config)
{
	if (!ft_strncmp(line, "NO", 2))
		return (parse_north_tex(line, config));
	if (!ft_strncmp(line, "SO", 2))
		return (parse_south_tex(line, config));
	if (!ft_strncmp(line, "WE", 2))
		return (parse_west_tex(line, config));
	if (!ft_strncmp(line, "EA", 2))
		return (parse_east_tex(line, config));
	return (1);
}

static int	parse_line(char *line, t_config *config)
{	
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_strtrim(line, " \n");
	if (!trimmed_line)
		return (0);
	if (trimmed_line[0] == '\0')
		return (free(trimmed_line), 1);
	if (is_path(trimmed_line))
		ret = parse_tex(trimmed_line, config);
	if (trimmed_line[0] == 'F')
		ret = parse_floor_color(trimmed_line, config);
	if (trimmed_line[0] == 'C')
		ret = parse_ceiling_color(trimmed_line, config);
	free(trimmed_line);
	return (ret);
}

t_config	*parse_file(int fd, t_config *config)
{
	char		*line;
	
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, config))
		{
			free(line);
			free_config(config);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	// TEST
	// print_config_elements(config);
	return (config);
}
