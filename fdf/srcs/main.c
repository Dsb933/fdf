/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:30:00 by alborges          #+#    #+#             */
/*   Updated: 2025/07/15 19:27:57 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	(void)argv;
	if (argc != 2)
	{
		write(2, "Usage: ./fdf <filename.fdf>\n", 28);
		return (1);
	}
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (1);
	fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "FdF");
	if (!fdf.win)
		return (1);
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, close_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
