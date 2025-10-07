/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborges <alborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:35:47 by alborges          #+#    #+#             */
/*   Updated: 2025/10/07 02:00:51 by alborges         ###   ########.fr       */
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
	int		x;
	int		y;
	int		z;
	int		color;
}t_point;

typedef struct s_map
{
	t_point		**points;
	int			width;
	int			height;
}t_map;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
	double		zoom;
	int			offset_x;
	int			offset_y;
}t_fdf;

typedef struct s_xy
{
	int		x;
	int		y;
}t_xy;

typedef struct s_bounds
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
}t_bounds;

typedef struct s_proj
{
	int		scale_z;
	double	zoom;
	int		offset_x;
	int		offset_y;
}t_proj;

int			ft_atoi_hex(char *str);
int			count_words(char *str);
int			allocate_map_points(t_map *map, int fd, char *first_line);
void		set_point_from_token(t_point *pt, char *token, int x, int y);
int			close_hook(t_fdf *fdf);
int			key_hook(int keycode, t_fdf *fdf);
t_map		*parse_file(char *filename);
void		put_pixel(t_fdf *fdf, int x, int y, int color);
void		render_map(t_fdf *fdf);
void		draw_line(t_fdf *fdf, t_xy a, t_xy b, int color);
void		project_point(t_point *point, int *screen_x, int *screen_y);
void		project_point_adaptive(t_point *point, t_xy *out, t_proj *p);
void		get_map_bounds(t_map *map, int *min_z, int *max_z);
void		get_projected_bounds(t_map *map, t_proj *p, t_bounds *b);
void		zoom_view(t_fdf *fdf, int direction);
void		reset_view(t_fdf *fdf);
void		move_view(t_fdf *fdf, int direction);

#endif