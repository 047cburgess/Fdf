/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:46:22 by caburges          #+#    #+#             */
/*   Updated: 2025/01/22 14:46:34 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_the_scale(t_point *point, float scale)
{
	point->ix = point->ix * scale;
	point->iy = point->iy * scale;
}

void	apply_the_offset(t_map *map, t_point *point)
{
	point->ix += map->offset_x;
	point->iy += map->offset_y;
}

void	find_max_and_min(t_map *map, t_point **matrix)
{
	int	row;
	int	col;

	row = 0;
	map->ix_min = matrix[0][0].ix;
	map->ix_max = matrix[0][0].ix;
	map->iy_min = matrix[0][0].iy;
	map->iy_max = matrix[0][0].iy;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (matrix[row][col].ix < map->ix_min)
				map->ix_min = matrix[row][col].ix;
			if (matrix[row][col].ix > map->ix_max)
				map->ix_max = matrix[row][col].ix;
			if (matrix[row][col].iy < map->iy_min)
				map->iy_min = matrix[row][col].iy;
			if (matrix[row][col].iy > map->iy_max)
				map->iy_max = matrix[row][col].iy;
			col++;
		}
		row++;
	}
}
