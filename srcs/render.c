/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:33:07 by alborges          #+#    #+#             */
/*   Updated: 2025/10/07 02:00:51 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_drawctx
{
	int		scale_z;
	int		offset_x;
	int		offset_y;
}t_drawctx;

static void	calculate_scaling(t_fdf *fdf, int *scale_z)
{
	int	min_z;
	int	max_z;

	get_map_bounds(fdf->map, &min_z, &max_z);
	if (max_z - min_z > 0)
		*scale_z = 100 / (max_z - min_z);
	else
		*scale_z = 20;
	if (*scale_z < 5)
		*scale_z = 5;
	if (*scale_z > 50)
		*scale_z = 50;
}

static void	calculate_offsets(t_fdf *fdf, t_drawctx *c)
{
	t_bounds	b;
	t_proj		p;

	p.scale_z = c->scale_z;
	p.zoom = 1.0;
	p.offset_x = 0;
	p.offset_y = 0;
	get_projected_bounds(fdf->map, &p, &b);
	c->offset_x = (WIDTH - (b.max_x - b.min_x)) / 2 - b.min_x;
	c->offset_y = (HEIGHT - (b.max_y - b.min_y)) / 2 - b.min_y;
}

static void	draw_neighbors(t_fdf *fdf, t_proj *proj, int x, int y)
{
	t_xy	p1;
	t_xy	p2;

	project_point_adaptive(&fdf->map->points[y][x], &p1, proj);
	if (x < fdf->map->width - 1)
	{
		project_point_adaptive(&fdf->map->points[y][x + 1], &p2, proj);
		draw_line(fdf, p1, p2, fdf->map->points[y][x].color);
	}
	if (y < fdf->map->height - 1)
	{
		project_point_adaptive(&fdf->map->points[y + 1][x], &p2, proj);
		draw_line(fdf, p1, p2, fdf->map->points[y][x].color);
	}
}

static void	render_grid_lines(t_fdf *fdf, t_drawctx *c)
{
	int		x;
	int		y;
	t_proj	proj;

	proj.scale_z = c->scale_z;
	proj.zoom = fdf->zoom;
	proj.offset_x = c->offset_x + fdf->offset_x;
	proj.offset_y = c->offset_y + fdf->offset_y;
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			draw_neighbors(fdf, &proj, x, y);
			x++;
		}
		y++;
	}
}

void	render_map(t_fdf *fdf)
{
	t_drawctx	c;

	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	calculate_scaling(fdf, &c.scale_z);
	calculate_offsets(fdf, &c);
	render_grid_lines(fdf, &c);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
