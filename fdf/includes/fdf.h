/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:35:47 by alborges          #+#    #+#             */
/*   Updated: 2025/07/15 20:37:49 by alborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "get_next_line.h"
# include <fcntl.h>

/* ========== DEFINES ========== */
# define WIDTH 1920
# define HEIGHT 1080
# define ESC_KEY 65307

/* ========== STRUCTURES ========== */
typedef struct s_point
{
    int     x;
    int     y;
    int     z;
    int     color;
} t_point;

typedef struct s_map
{
    t_point **points;
    int     width;
    int     height;
} t_map;

typedef struct s_fdf
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    t_map   *map;
} t_fdf;

int	close_hook(t_fdf *fdf);
int	key_hook(int keycode, t_fdf *fdf);


#endif