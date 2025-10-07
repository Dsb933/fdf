/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:00:00 by alborges          #+#    #+#             */
/*   Updated: 2025/10/07 02:00:52 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *str)
{
	int	count;
	int	i;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

int	ft_atoi_hex(char *str)
{
	int		result;
	int		i;
	char	c;

	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		c = str[i];
		result *= 16;
		if (c >= '0' && c <= '9')
			result += c - '0';
		else if (c >= 'A' && c <= 'F')
			result += c - 'A' + 10;
		else if (c >= 'a' && c <= 'f')
			result += c - 'a' + 10;
		i++;
	}
	return (result);
}

void	set_point_from_token(t_point *pt, char *token, int x, int y)
{
	char	**c;

	pt->x = x;
	pt->y = y;
	if (ft_strchr(token, ','))
	{
		c = ft_split(token, ',');
		pt->z = ft_atoi(c[0]);
		pt->color = ft_atoi_hex(c[1]);
		free(c[0]);
		free(c[1]);
		free(c);
	}
	else
	{
		pt->z = ft_atoi(token);
		pt->color = 0xFFFFFF;
	}
}

int	allocate_map_points(t_map *map, int fd, char *line)
{
	int	y;

	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
	{
		free(line);
		close(fd);
		return (-1);
	}
	y = 0;
	while (y < map->height)
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
		{
			while (--y >= 0)
				free(map->points[y]);
			free(map->points);
			free(line);
			close(fd);
			return (-1);
		}
		y++;
	}
	return (0);
}

void	project_point(t_point *point, int *screen_x, int *screen_y)
{
	*screen_x = (point->x - point->y) * 20;
	*screen_y = (point->x + point->y) * 10 - point->z;
	*screen_x += WIDTH / 2;
	*screen_y += HEIGHT / 2;
}
