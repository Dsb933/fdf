/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:30:00 by alborges          #+#    #+#             */
/*   Updated: 2025/09/29 19:13:23 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf, char *filename)
{
	fdf->map = parse_file(filename);
	if (!fdf->map)
	{
		write(2, "Error: Cannot read file\n", 24);
		exit(1);
	}
	fdf->zoom = 1.0;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit(1);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	if (!fdf->win)
		exit(1);
}

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	if (map->points)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->points[y])
				free(map->points[y]);
			y++;
		}
		free(map->points);
	}
	free(map);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf <filename.fdf>\n", 28);
		return (1);
	}
	init_fdf(&fdf, argv[1]);
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, close_hook, &fdf);
	render_map(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
