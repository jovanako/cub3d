/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:47:23 by jkovacev          #+#    #+#             */
/*   Updated: 2026/04/16 16:45:05 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "cub3d.h"
#include "mlx.h"

static int	alloc_map_grid(t_game *game, int count)
{
	game->map.height = count;
	game->map.grid = ft_calloc((game->map.height + 1), sizeof(char *));
	if (!game->map.grid)
		return (print_error_and_return("Malloc failed\n", 0));
	return (1);
}

static int	calculate_map_height(char *arg, t_game *game)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_error_and_return("Open failed\n", 0));
	line = get_next_line(fd);
	while (line)
	{
		if (is_map(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (alloc_map_grid(game, count));
}

static t_game	*create_game(char *path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (print_error("Malloc failed\n"), NULL);
	if (!calculate_map_height(path, game))
		return (free(game), NULL);
	return (game);
}

static int	parse_game_file(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (deep_free_game(game),
			print_error_and_return("Open failed\n", 0));
	if (!parse_file(fd, game))
		return (close(fd), 0);
	close(fd);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (!validate_args(argc, argv[1]))
		return (1);
	game = create_game(argv[1]);
	if (!game)
		return (1);
	if (!parse_game_file(argv[1], game))
		return (1);
	if (!init_game(game))
		return (deep_free_game(game), 1);
	if (!init_image(game))
		return (deep_free_game(game), 1);
	if (!load_textures(game))
		return (deep_free_game(game), 1);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
	deep_free_game(game);
	return (0);
}
