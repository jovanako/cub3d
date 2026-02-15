/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:08:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 15:21:10 by jkovacev         ###   ########.fr       */
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

static int	parse_color(char *line, t_config *config)
{
	char	*start;

	start = skip_leading_ws(line);
	if (start[0] == 'F')
		return (parse_floor_color(start, config));
	if (start[0] == 'C')
		return (parse_ceiling_color(start, config));
	return (0);
}

static int	parse_line(char *line, t_game *game)
{	
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (0);
	if (trimmed_line[0] == '\0')
		return (free(trimmed_line), 1);
	if (is_path(trimmed_line))
		ret = parse_tex(trimmed_line, &game->config);
	else if (ft_strchr(trimmed_line, 'F') || ft_strchr(trimmed_line, 'C'))
		ret = parse_color(trimmed_line, &game->config);
	else if (has_config(&game->config) && is_map(trimmed_line))
		ret = parse_grid(line, &game->map);
	else if (has_config(&game->config) && !is_map(trimmed_line))
		ret = print_error_and_return("Invalid line in map\n", 0);
	free(trimmed_line);	
	return (ret);
}

t_game	*parse_file(int fd, t_game *game)
{
	char		*line;
	
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, game))
		{
			free(line);
			deep_free_game(game);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	// TEST
	// print_config_elements(config);
	return (game);
}
