/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:37 by caburges          #+#    #+#             */
/*   Updated: 2025/01/22 14:43:42 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W_WIDTH 1080
# define W_HEIGHT 900
# define PADDING 0.9
# define PURPLE 0x4b0082
# define WHITE 0xffffff
# define YELLOW 0xffa500
# define PINK 0xff69b4
# define TEAL 0x008080
# define CORAL 0xff7f50
# define BLUE 0x0000ff
# define FUSCHIA 0xff00ff
# define BRIGHT_GREEN 0x00ff00
# define RED 0xff0000

# define LOWEST PURPLE
# define MID_LOW BLUE
# define MID BRIGHT_GREEN
# define MID_HIGH YELLOW
# define HIGHEST RED

# include <X11/X.h>
# include <X11/keysym.h> 
# include <mlx.h>
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	float	ix;
	float	iy;
	int		colour;

}	t_point;

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
}	t_colour;

typedef struct s_map
{
	int		width;
	int		height;
	float	scale;
	float	z_scale;
	int		z_range;
	int		z_min;
	int		z_max;
	t_point	**matrix;

	void	*win_ptr;
	void	*mlx_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_l;
	int		end;

	float	ix_min;
	float	ix_max;
	float	iy_min;
	float	iy_max;
	float	ix_width;
	float	iy_width;
	int		offset_x;
	int		offset_y;
}	t_map;

// Map initialisation
void	initialise_map(t_map *map, char *file);
void	initialise_mlx(t_map *map);
t_point	**get_memory(t_map *map);
int		set_width_and_height(t_map *map, char *file);
void	fill_row(t_map *map, int row, char **split_row);
int		fill_points(t_map *map, char *file);
int		count_words(char *str);
void	check_fd(int *fd, char *file);
void	free_split(char **nums);

// Map clean up / shut down
void	free_map(t_map *map);
int		shut_down(t_map *map, int status);

// Maths
void	set_iso(t_map *map);
void	set_2d_point(t_point *point);
void	apply_the_scale(t_point *point, float scale);
void	apply_the_offset(t_map *map, t_point *point);
void	scale_points(t_map *map);
void	offset_points(t_map *map);
void	find_max_and_min(t_map *map, t_point **matrix);

// Colours
void	set_z_range(t_map *map, t_point **matrix, int mwidth, int mheight);
int		get_colour(t_map *map, int z);
void	set_colours(t_map *map, t_point **matrix);

// Drawing
void	draw_image(t_map *map);
void	draw_line(t_point from, t_point to, t_map *map);
void	my_mlx_pixel_put(t_map *map, int x, int y, int colour);

#endif
