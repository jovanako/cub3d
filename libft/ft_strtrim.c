/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:33:50 by jkovacev          #+#    #+#             */
/*   Updated: 2026/02/12 16:57:44 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_equal(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*generate_trimmed_copy(char const *s1,
		char *copy, size_t start, size_t copy_size)
{
	size_t	i;

	i = 0;
	while (i < copy_size)
	{
		copy[i] = s1[start];
		i++;
		start++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	size_t	end;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_equal(s1[start], set))
		start++;
	while ((end > start) && is_equal(s1[end - 1], set))
		end--;
	copy = (char *)malloc((end - start + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	return (generate_trimmed_copy(s1, copy, start, end - start));
}
