/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:35:56 by caburges          #+#    #+#             */
/*   Updated: 2025/01/22 14:36:13 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_z_range(t_map *map, t_point **matrix, int mwidth, int mheight)
{
	int	row;
	int	col;

	map->z_min = matrix[0][0].z;
	map->z_max = matrix[0][0].z;
	row = 0;
	while (row < mheight)
	{
		col = 0;
		while (col < mwidth)
		{
			if (matrix[row][col].z < map->z_min)
				map->z_min = matrix[row][col].z;
			if (matrix[row][col].z > map->z_max)
				map->z_max = matrix[row][col].z;
			col++;
		}
		row++;
	}
	map->z_range = (map->z_max - map->z_min);
}

int	get_colour(t_map *map, int z)
{
	int	mid;
	int	low_mid;
	int	high_mid;

	if (z == 0 && map->z_min < 0)
		return (WHITE);
	mid = (map->z_min + map->z_max) / 2;
	low_mid = (map->z_min + mid) / 2;
	high_mid = (mid + map->z_max) / 2;
	if (z == map->z_min)
		return (LOWEST);
	else if (z > map->z_min && z <= low_mid)
		return (MID_LOW);
	else if (z > low_mid && z <= mid)
		return (MID);
	else if (z > mid && z <= high_mid)
		return (MID_HIGH);
	else
		return (HIGHEST);
}

void	set_colours(t_map *map, t_point **matrix)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			matrix[row][col].colour = get_colour(map, matrix[row][col].z);
			col++;
		}
		row++;
	}
}
