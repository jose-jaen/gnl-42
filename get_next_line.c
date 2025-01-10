/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaen-de <jjaen-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:31:26 by jjaen-de          #+#    #+#             */
/*   Updated: 2024/10/20 13:31:22 by jjaen-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE

# define BUFFER_SIZE 9

#endif

static char	*ft_append(char *buffer, char *buf)
{
	char	*joint;

	joint = ft_strjoin(buffer, buf);
	free(buffer);
	return (joint);
}

static char	*ft_read(int fd, char *leftover)
{
	int		n_bytes;
	char	*buffer;
	char	*is_match;

	if (!leftover)
	{
		leftover = ft_setup_leftover(leftover);
		if (!leftover)
			return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(leftover), NULL);
	is_match = NULL;
	n_bytes = BUFFER_SIZE;
	while (!is_match && n_bytes != 0)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes < 0)
			return (free(buffer), free(leftover), NULL);
		buffer[n_bytes] = '\0';
		leftover = ft_append(leftover, buffer);
		is_match = ft_strchr(buffer, '\n');
	}
	return (free(buffer), leftover);
}

static char	*ft_extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*line;
	size_t	n_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	n_buffer = ft_strlen(buffer);
	line = (char *)malloc((n_buffer - i + 1) * sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}
