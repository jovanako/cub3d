/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:47:37 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 20:40:46 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_string(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;

	s_len = ft_strlen(s);
	dup = (char *)malloc(s_len * sizeof(char) + 1);
	if (dup)
	{
		dup = copy_string(dup, s, s_len);
		return (dup);
	}
	ft_print_error("Failed malloc\n");
	return (NULL);
}
