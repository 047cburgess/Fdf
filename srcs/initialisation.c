/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:05:00 by caburges          #+#    #+#             */
/*   Updated: 2025/01/22 17:24:09 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialise_map(t_map *map, char *file)
{
	map->mlx_ptr = NULL;
	map->win_ptr = NULL;
	map->img = NULL;
	map->z_scale = 1;
	map->matrix = NULL;
	if (!set_width_and_height(map, file))
	{
		ft_putendl_fd("ERROR: invalid map", 2);
		exit(EXIT_FAILURE);
	}
	map->matrix = get_memory(map);
	if (!map->matrix)
	{
		ft_putendl_fd("ERROR: malloc fail", 2);
		exit(EXIT_FAILURE);
	}
	if (!fill_points(map, file))
	{
		free_map(map);
		ft_putendl_fd("ERROR: malloc fail", 2);
		exit(EXIT_FAILURE);
	}
}

void	initialise_mlx(t_map *map)
{
	map->mlx_ptr = mlx_init();
	if (!map->mlx_ptr)
	{
		ft_putendl_fd("ERROR: failed initialising mlx", 2);
		shut_down(map, EXIT_FAILURE);
	}
	map->win_ptr = mlx_new_window(map->mlx_ptr, W_WIDTH, W_HEIGHT, "FDF");
	if (!map->win_ptr)
	{
		ft_putendl_fd("ERROR: failed initialising mlx window", 2);
		shut_down(map, EXIT_FAILURE);
	}
	map->img = mlx_new_image(map->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!map->img)
	{
		ft_putendl_fd("ERROR: failed to get mlx new image", 2);
		shut_down(map, EXIT_FAILURE);
	}
	map->addr = mlx_get_data_addr(map->img, &map->bpp, &map->l_l, &map->end);
}

int	read_row(t_map *map, int fd, int row)
{
	char	*raw_row;
	char	**split_row;

	raw_row = get_next_line(fd);
	if (!raw_row)
		return (ft_putendl_fd("ERROR: reading file", 2), 0);
	split_row = ft_split(raw_row, ' ');
	free(raw_row);
	if (!split_row)
		return (ft_putendl_fd("ERROR: Split failed", 2), 0);
	fill_row(map, row, split_row);
	free_split(split_row);
	return (1);
}

int	fill_points(t_map *map, char *file)
{
	int		fd;
	int		row;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("ERROR: Couldn't open file", 2), 0);
	row = 0;
	while ((row < map->height) && read_row(map, fd, row))
		row++;
	get_next_line(-1);
	close(fd);
	if (row == map->height)
		return (1);
	return (0);
}

void	fill_row(t_map *map, int row, char **split_row)
{
	int	col;

	col = 0;
	while (col < map->width)
	{
		map->matrix[row][col].x = col;
		map->matrix[row][col].y = row;
		map->matrix[row][col].z = ft_atoi(split_row[col]);
		col++;
	}
}
