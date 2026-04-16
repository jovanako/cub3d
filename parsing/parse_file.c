/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:08:15 by jkovacev          #+#    #+#             */
/*   Updated: 2026/04/16 16:58:08 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	parse_content_line(char *trimmed_line, char *line, t_game *game,
		t_parse_state *state)
{
	if (state->map_ended)
		return (print_error_and_return("Map must be the last element\n", 0));
	if (is_path(trimmed_line))
		return (parse_tex(trimmed_line, &game->config));
	if (ft_strchr(trimmed_line, 'F') || ft_strchr(trimmed_line, 'C'))
		return (parse_color(trimmed_line, &game->config));
	return (parse_map_line(trimmed_line, line, game, state));
}

static int	parse_line(char *line, t_game *game, t_parse_state *state)
{
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (0);
	ret = parse_empty_line(trimmed_line, state);
	if (ret != -1)
		return (ret);
	ret = parse_content_line(trimmed_line, line, game, state);
	free(trimmed_line);
	return (ret);
}

static int	read_file_lines(int fd, t_game *game)
{
	char			*line;
	t_parse_state	state;

	state.map_started = 0;
	state.map_ended = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, game, &state))
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

static int	finalize_game(t_game *game)
{
	game->map.width = calculate_map_width(game->map.grid);
	if (!normalize_map(&game->map))
		return (0);
	set_player(game);
	if (!validate_map(&game->map, &game->player))
		return (0);
	return (1);
}

t_game	*parse_file(int fd, t_game *game)
{
	if (!read_file_lines(fd, game) || !finalize_game(game))
	{
		deep_free_game(game);
		return (NULL);
	}
	return (game);
}
