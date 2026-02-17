/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:08:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:33:51 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	has_config(t_config *config)
{
	if (config)
	{
		return (config->north.path && config->south.path
				&& config->west.path && config->east.path
				&& config->floor_color &&config->ceiling_color);
	}
	print_error("Texture values missing\n");
	return (0);
}

static int	calculate_map_width(char **grid)
{
	int	i;
	int	len;
	int	width;

	i = 0;
	len = 0;
	width = 0;
	if (!grid)
		return (0);
	while (grid[i])
	{
		len = (int)ft_strlen(grid[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
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
	game->map.width = calculate_map_width(game->map.grid);
	if (!map_validation(&game->map))
		return (NULL);
	return (game);
}
