/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:41:29 by alborges          #+#    #+#             */
/*   Updated: 2025/10/07 02:00:52 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_dstep
{
	double	ix;
	double	iy;
	double	s;
}	t_dstep;

void	project_point_adaptive(t_point *point, t_xy *out, t_proj *p)
{
	out->x = (point->x - point->y) * 20 * p->zoom;
	out->y = (point->x + point->y) * 10 * p->zoom - point->z * p->scale_z;
	out->x += WIDTH / 2 + p->offset_x;
	out->y += HEIGHT / 2 + p->offset_y;
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = y * fdf->line_length
			+ x * (fdf->bits_per_pixel / 8);
		dst = fdf->addr + offset;
		*(unsigned int *)dst = color;
	}
}

static t_dstep	step_line(t_xy a, t_xy b)
{
	t_dstep	st;
	double	dx;
	double	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	st.s = fabs(dx);
	if (fabs(dy) > st.s)
		st.s = fabs(dy);
	st.ix = dx / st.s;
	st.iy = dy / st.s;
	return (st);
}

void	draw_line(t_fdf *fdf, t_xy a, t_xy b, int color)
{
	double	x;
	double	y;
	int		i;
	t_dstep	st;

	if (a.x == b.x && a.y == b.y)
	{
		put_pixel(fdf, a.x, a.y, color);
		return ;
	}
	st = step_line(a, b);
	x = a.x;
	y = a.y;
	i = 0;
	while (i <= (int)st.s)
	{
		put_pixel(fdf, (int)round(x), (int)round(y), color);
		x += st.ix;
		y += st.iy;
		i++;
	}
}
