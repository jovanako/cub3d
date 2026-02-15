/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:01:55 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/15 22:46:28 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_print_error(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
}

int	find_new_line(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static void	copy(char *dst, char *src, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*my_substr(char **s, int start, int len)
{
	char	*result;

	result = malloc((len + 1) * sizeof(char));
	if (!result)
	{
		free(*s);
		*s = NULL;
		gnl_print_error("Malloc failed\n");
		return (NULL);
	}
	copy(result, *s + start, len);
	result[len] = '\0';
	return (result);
}

void	append(char **line_buf, char *read_buf, int bytes_read)
{
	char	*temp;
	int		line_len;

	temp = *line_buf;
	line_len = ft_strlen(*line_buf);
	*line_buf = malloc((line_len + bytes_read + 1) * sizeof(char));
	if (!(*line_buf))
	{
		free(temp);
		gnl_print_error("Malloc failed\n");
		return ;
	}
	(*line_buf)[line_len + bytes_read] = '\0';
	copy(*line_buf, temp, line_len);
	free(temp);
	copy(*line_buf + line_len, read_buf, bytes_read);
}
