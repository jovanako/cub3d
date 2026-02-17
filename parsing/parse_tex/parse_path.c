/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:19:53 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/17 11:29:39 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"

static int	is_valid_path(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*get_path(char *line)
{
	char	*temp;
	char	*path;

	temp = ft_substr(line, 2, ft_strlen(line) - 2);
	if (!temp)
		return (NULL);
	path = ft_strtrim(temp, " ");
	free(temp);
	if (!path)
		return (NULL);
	if (!is_valid_path(path))
	{
		free(path);
		return (print_error("Error opening file\n"), NULL);
	}
	return (path);
}