/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:26:28 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 15:11:23 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*skip_leading_ws(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

int is_map(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i])
	{
		if ((line[i] == 'N' && line[i + 1] == 'O')
			|| (line[i] == 'S' && line[i + 1] == 'O')
			|| (line[i] == 'W' && line[i + 1] == 'E')
			|| (line[i] == 'E' && line[i + 1] == 'A')
			|| line[i] == 'F' || line[i] == 'C')
			return (0);
		if (line[i] == '1')
			return (1);
		return (0);
	}
	return (0);
}
