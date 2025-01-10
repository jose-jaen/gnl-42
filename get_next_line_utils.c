/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaen-de <jjaen-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:09 by jjaen-de          #+#    #+#             */
/*   Updated: 2024/10/20 13:13:09 by jjaen-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_setup_leftover(char *leftover)
{
	leftover = (char *)malloc(sizeof(char));
	if (!leftover)
		return (NULL);
	leftover[0] = '\0';
	return (leftover);
}

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	new_c;

	new_c = (unsigned char)c;
	if (!s && new_c)
		return (NULL);
	while (*s)
	{
		if (*s == new_c)
			return ((char *)s);
		s++;
	}
	if (new_c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n_s1;
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	n_s1 = ft_strlen(s1);
	res = (char *)malloc((n_s1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
