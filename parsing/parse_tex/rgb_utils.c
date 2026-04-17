/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:22:22 by jkovacev          #+#    #+#             */
/*   Updated: 2026/04/17 09:48:35 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"

int	skip_whitespace(char *line, int i)
{
	if (line[i] && line[i] == ' ')
	{
		while (line[i] && line[i] == ' ')
			i++;		
	}
	return (i);
}

static int	is_valid_rgb_num(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i] && ft_isdigit(line[i]))
	{
		len++;
		i++;
	}
	if (len >= 1 && len <= 3)
		return (i);
	return (0);
}

int	skip_color_identifier(char *line, int i)
{
	i = skip_whitespace(line, i);
	if (line[i] != 'F' && line[i] != 'C')
		return (print_error_and_return("Invalid input for color\n", 0));
	i++;
	i = skip_whitespace(line, i);
	return (i);
}

int	skip_rgb_num(char *line, int i)
{
	i = is_valid_rgb_num(line, i);
	if (!i)
		return (print_error_and_return("Invalid input for color\n", 0));
	if (line[i] && line[i] == ' ')
		i = skip_whitespace(line, i);
	return (i);
}

int	skip_comma(char *line, int i)
{
	if (!line[i] || line[i] != ',')
		return (print_error_and_return("Invalid input for color\n", 0));
	i++;
	if (line[i] && line[i] == ' ')
		i = skip_whitespace(line, i);
	return (i);
}