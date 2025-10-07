/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:47:31 by alborges          #+#    #+#             */
/*   Updated: 2025/09/29 21:32:21 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_view(t_fdf *fdf, int direction)
{
	if (direction > 0)
	{
		fdf->zoom *= 1.1;
		if (fdf->zoom > 5.0)
			fdf->zoom = 5.0;
	}
	else
	{
		fdf->zoom /= 1.1;
		if (fdf->zoom < 0.1)
			fdf->zoom = 0.1;
	}
	render_map(fdf);
}

void	reset_view(t_fdf *fdf)
{
	fdf->zoom = 1.0;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	render_map(fdf);
}

void	move_view(t_fdf *fdf, int direction)
{
	if (direction == 0)
		fdf->offset_x -= 20;
	else if (direction == 1)
		fdf->offset_x += 20;
	else if (direction == 2)
		fdf->offset_y -= 20;
	else if (direction == 3)
		fdf->offset_y += 20;
	render_map(fdf);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0);
	}
	else if (keycode == 61)
		zoom_view(fdf, 1);
	else if (keycode == 45)
		zoom_view(fdf, -1);
	else if (keycode == 114)
		reset_view(fdf);
	else if (keycode == 65361)
		move_view(fdf, 0);
	else if (keycode == 65362)
		move_view(fdf, 2);
	else if (keycode == 65363)
		move_view(fdf, 1);
	else if (keycode == 65364)
		move_view(fdf, 3);
	return (0);
}

int	close_hook(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}
