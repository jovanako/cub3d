/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:47:23 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 13:56:24 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	printf("map height: %d\n", game->map.height);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (print_error_and_return("Open failed\n", 1));
	if (!parse_file(fd, game))
	{
		close(fd);
		return (1);
	}
	close(fd);
	deep_free_game(game);
	return (0);
}
