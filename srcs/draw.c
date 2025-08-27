/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:22:37 by caburges          #+#    #+#             */
/*   Updated: 2025/01/22 14:42:49 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_map *map, int x, int y, int colour)
{
	char	*dst;

	if ((x >= 0 && x < W_WIDTH) && (y > 0 && y < W_HEIGHT))
	{
		dst = map->addr + (y * map->l_l + x * (map->bpp / 8));
		*(unsigned int *)dst = colour;
	}
}

void	draw_image(t_map *map)
{
	t_point	**matrix;
	int		i;
	int		j;

	matrix = map->matrix;
	set_z_range(map, map->matrix, map->width, map->height);
	set_colours(map, map->matrix);
	set_iso(map);
	scale_points(map);
	offset_points(map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (j < map->width - 1)
				draw_line(matrix[i][j], matrix[i][j + 1], map);
			if (i < map->height - 1)
				draw_line(matrix[i][j], matrix[i + 1][j], map);
			j++;
		}
		i++;
	}
}

int	grad(int from, int to, int current_pos, float max)
{
	float		ratio;
	t_colour	c;

	ratio = current_pos / max;
	c.r = ((1 - ratio) * (from >> 16 & 0xFF) + ratio * (to >> 16 & 0xFF));
	c.g = ((1 - ratio) * (from >> 8 & 0xFF) + ratio * (to >> 8 & 0xFF));
	c.b = ((1 - ratio) * (from & 0xFF) + ratio * (to & 0xFF));
	return ((c.r << 16) | (c.g << 8) | c.b);
}

void	draw_line(t_point from, t_point to, t_map *map)
{
	float	x_step;
	float	y_step;
	float	max;
	int		colour;
	int		i;

	x_step = to.ix - from.ix;
	y_step = to.iy - from.iy;
	max = fmax(fabs(x_step), fabs(y_step));
	x_step = x_step / max;
	y_step = y_step / max;
	i = 0;
	while (i <= (int)max)
	{	
		colour = grad(from.colour, to.colour, i, max);
		my_mlx_pixel_put(map, round(from.ix), round(from.iy), colour);
		from.ix = from.ix + x_step;
		from.iy = from.iy + y_step;
		i++;
	}
}
