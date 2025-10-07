/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:07:07 by alborges          #+#    #+#             */
/*   Updated: 2025/05/20 20:29:49 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

char	*read_to_buffer(int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return ((char *)-1);
	}
	if (bytes_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

static char	*update_remainder(char *remainder, char *buffer)
{
	char	*new_remainder;

	if (!remainder)
		return (ft_strdup(buffer));
	new_remainder = ft_strjoin(remainder, buffer);
	free(remainder);
	return (new_remainder);
}

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*new_remainder;
	char	*newline_pos;

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1);
		new_remainder = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = new_remainder;
	}
	else
	{
		if (**remainder == '\0')
		{
			free(*remainder);
			*remainder = NULL;
			return (NULL);
		}
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

int	check_fd(int fd, char *remainder)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
	{
		if (remainder)
		{
			free(remainder);
			remainder = NULL;
		}
		return (-1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	char		*buffer;

	if (check_fd(fd, remainder[fd]) == -1)
		return (NULL);
	while (!ft_strchr(remainder[fd], '\n'))
	{
		buffer = read_to_buffer(fd);
		if (buffer == (char *)-1)
			return ((free(remainder[fd]), remainder[fd] = NULL, NULL));
		if (!buffer)
			break ;
		remainder[fd] = update_remainder(remainder[fd], buffer);
		free(buffer);
		if (!remainder[fd])
			return (NULL);
	}
	if (!remainder[fd] || !*remainder[fd])
		return (free(remainder[fd]), remainder[fd] = NULL, NULL);
	return (line = extract_line(&remainder[fd]), line);
}
