/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:31:48 by alborges          #+#    #+#             */
/*   Updated: 2025/10/07 02:00:50 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_file_lines(char *filename)
{
	int		hfd;
	char	*tmp;
	int		h;

	h = 0;
	hfd = open(filename, O_RDONLY);
	if (hfd < 0)
		return (-1);
	tmp = get_next_line(hfd);
	while (tmp)
	{
		h++;
		free(tmp);
		tmp = get_next_line(hfd);
	}
	close(hfd);
	return (h);
}

static void	fill_map_line(t_map *map, char *line, int y)
{
	char	**numbers;
	int		x;

	numbers = ft_split(line, ' ');
	if (!numbers)
		return ;
	x = 0;
	while (numbers[x] && x < map->width)
	{
		set_point_from_token(&map->points[y][x], numbers[x], x, y);
		free(numbers[x]);
		x++;
	}
	free(numbers);
}

static int	get_map_dimensions(t_map *map, char *filename, int *fd, char **line)
{
	int	h;

	h = count_file_lines(filename);
	if (h <= 0)
		return (-1);
	map->height = h;
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (-1);
	*line = get_next_line(*fd);
	if (!*line)
	{
		close(*fd);
		return (-1);
	}
	map->width = count_words(*line);
	return (0);
}

static void	fill_map_grid(t_map *map, int fd, char *first_line)
{
	int		y;
	char	*line;

	fill_map_line(map, first_line, 0);
	y = 1;
	line = NULL;
	while (y < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		fill_map_line(map, line, y);
		free(line);
		y++;
	}
}

t_map	*parse_file(char *filename)
{
	t_map	*map;
	int		fd;
	char	*line;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (get_map_dimensions(map, filename, &fd, &line) == -1)
	{
		free(map);
		return (NULL);
	}
	if (allocate_map_points(map, fd, line) == -1)
	{
		free(map);
		return (NULL);
	}
	fill_map_grid(map, fd, line);
	close(fd);
	return (map);
}
