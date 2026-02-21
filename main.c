/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:47:23 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/20 21:40:29 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

// void print_arr(char **arr, int size)
// {
// 	for (int i = 0; i < size; i++)
// 		printf("arr[]: %s\n", arr[i]);
// }

// void	print_game(t_game *game)
// {
// 	print_config_elements(&game->config);
// 	printf("\n---Map---\n");
// 	print_arr(game->map.grid, game->map.height);
// 	printf("map height: %d\nmap width: %d\n", game->map.height, game->map.width);
// 	printf("\n---Player---\n");
// 	printf("player x: %f\nplayer y: %f\n", game->player.x, game->player.y);
// 	printf("player dir x: %f\nplayer dir y: %f\n", game->player.dir_x, game->player.dir_y);
// 	printf("player plane x: %f\nplayer plane y: %f\n", game->player.plane_x, game->player.plane_y);
// }

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
	while(line)
	{
		if (is_map(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->map.height = count;
	game->map.grid = ft_calloc((game->map.height + 1), sizeof(char *));
	if (!game->map.grid)
		return (print_error_and_return("Malloc failed\n", 0));
	return (1);
}

int main(int argc, char *argv[])
{
	int		fd;
	t_game	*game;
	
	if (argc != 2)
		return (print_error_and_return("Invalid number of arguments\n", 1));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return(print_error("Malloc failed\n"), 1);
	if (!calculate_map_height(argv[1], game))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (print_error_and_return("Open failed\n", 1));
	if (!parse_file(fd, game))
	{
		close(fd);
		return (1);
	}
	// print_game(game);
	close(fd);
	deep_free_game(game);
	return (0);
}
