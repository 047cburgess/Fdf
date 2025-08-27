/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:32:22 by caburges          #+#    #+#             */
/*   Updated: 2025/01/24 11:29:11 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_2d_point(t_point *point)
{
	float	angle;
	float	radians;

	angle = 30;
	radians = angle * (M_PI / 180);
	point->ix = (point->x - point->y) * cos(radians);
	point->iy = (point->x + point->y) * sin(radians) - point->z;
}

void	set_iso(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			set_2d_point(&map->matrix[row][col]);
			col++;
		}
		row++;
	}
}

float	calculate_scale(t_map *map)
{
	float	img_width;
	float	img_height;
	float	factor_x;
	float	factor_y;

	find_max_and_min(map, map->matrix);
	img_width = map->ix_max - map->ix_min;
	img_height = map->iy_max - map->iy_min;
	if (img_width == 0)
		img_width = 1;
	if (img_height == 0)
		img_height = 1;
	factor_x = (W_WIDTH / img_width);
	factor_y = (W_HEIGHT / img_height);
	return (fmin(factor_x, factor_y) * PADDING);
}

void	scale_points(t_map *map)
{
	int	row;
	int	col;

	map->scale = calculate_scale(map);
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			apply_the_scale(&map->matrix[row][col], map->scale);
			col++;
		}
		row++;
	}
	map->ix_min *= map->scale;
	map->ix_max *= map->scale;
	map->iy_min *= map->scale;
	map->iy_max *= map->scale;
	map->ix_width = map->ix_max - map->ix_min;
	map->iy_width = map->iy_max - map->iy_min;
}

void	offset_points(t_map *map)
{
	int	row;
	int	col;

	map->offset_x = -map->ix_min + (W_WIDTH - map->ix_width) / 2;
	map->offset_y = -map->iy_min + (W_HEIGHT - map->iy_width) / 2;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			apply_the_offset(map, &map->matrix[row][col]);
			col++;
		}
		row++;
	}
}
