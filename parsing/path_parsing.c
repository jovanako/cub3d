/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:45:49 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/11 21:49:52 by jkovacev         ###   ########.fr       */
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

char	*trim_nl(char *s)
{
	size_t	len;
	char	*result;
	int		i;

	len = ft_strlen(s);
	result = malloc(len * sizeof(char));
	if (!result)
		return (print_error("Malloc failed\n"), NULL);
	i = 0;
	while (*s != '\n')
	{
		result[i] = *s;
		i++;
		s++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_path(char *direction)
{
	char	*start;
	
	start = ft_strchr(direction, '.');
	while (*start)
	{
		if (ft_isalpha(*start))
			break;
		start++;
	}
	if (!is_valid_path(start))
		return (print_error("Error opening file\n"), NULL);
	return (start);
}

int	parse_any_path(char *line, t_config *config)
{	
	char	*trimmed_line;

	trimmed_line = trim_nl(line);
	if (ft_strchr(trimmed_line, 'N'))
		return (parse_north_tex(trimmed_line, config));
	if (ft_strchr(trimmed_line, 'S'))
		return (parse_south_tex(trimmed_line, config));
	if (ft_strchr(trimmed_line, 'W'))
		return (parse_west_tex(trimmed_line, config));
	if (ft_strchr(trimmed_line, 'E'))
		return (parse_east_tex(trimmed_line, config));
	return (print_error_and_return("Path input missing\n", 0));
}
