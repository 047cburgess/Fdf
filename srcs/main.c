/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:53:12 by caburges          #+#    #+#             */
/*   Updated: 2025/01/22 17:24:11 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

int		do_keypress(int keysym, t_map *map);

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./fdf filename", 2);
		return (EXIT_FAILURE);
	}
	initialise_map(&map, av[1]);
	initialise_mlx(&map);
	mlx_key_hook(map.win_ptr, do_keypress, &map);
	mlx_hook(map.win_ptr, 17, 0, shut_down, &map);
	draw_image(&map);
	mlx_put_image_to_window(map.mlx_ptr, map.win_ptr, map.img, 0, 0);
	mlx_loop(map.mlx_ptr);
}

int	do_keypress(int keysym, t_map *map)
{
	if (keysym == XK_Escape)
	{
		shut_down(map, 0);
	}
	return (0);
}

void	free_map(t_map *map)
{
	int	row;

	row = 0;
	while (row < map->height)
	{
		free(map->matrix[row]);
		row++;
	}
	free(map->matrix);
}

int	shut_down(t_map *map, int status)
{
	if (map->img != NULL)
		mlx_destroy_image(map->mlx_ptr, map->img);
	if (map->win_ptr != NULL)
		mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	if (map->mlx_ptr != NULL)
		mlx_destroy_display(map->mlx_ptr);
	free(map->mlx_ptr);
	if (map)
		free_map(map);
	exit(status);
	return (0);
}

void	print_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			ft_putnbr_fd(map.matrix[i][j].z, 1);
			ft_putstr_fd(" ", 1);
			j++;
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
