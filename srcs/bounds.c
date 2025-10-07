/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:35:00 by alborges          #+#    #+#             */
/*   Updated: 2025/10/07 02:00:52 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_minmax(t_bounds *b, t_xy pt)
{
	if (pt.x < b->min_x)
		b->min_x = pt.x;
	if (pt.x > b->max_x)
		b->max_x = pt.x;
	if (pt.y < b->min_y)
		b->min_y = pt.y;
	if (pt.y > b->max_y)
		b->max_y = pt.y;
}

void	get_map_bounds(t_map *map, int *min_z, int *max_z)
{
	int	x;
	int	y;

	*min_z = map->points[0][0].z;
	*max_z = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z < *min_z)
				*min_z = map->points[y][x].z;
			if (map->points[y][x].z > *max_z)
				*max_z = map->points[y][x].z;
			x++;
		}
		y++;
	}
}

void	get_projected_bounds(t_map *map, t_proj *p, t_bounds *b)
{
	int		x;
	int		y;
	t_xy	pt;

	b->min_x = 1000000;
	b->max_x = -1000000;
	b->min_y = 1000000;
	b->max_y = -1000000;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			project_point_adaptive(&map->points[y][x], &pt, p);
			update_minmax(b, pt);
			x++;
		}
		y++;
	}
}
