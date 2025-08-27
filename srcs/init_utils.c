/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:22:47 by caburges          #+#    #+#             */
/*   Updated: 2025/01/21 11:22:51 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (*str)
		{
			while (*str == ' ')
				str++;
			if (*str != '\0')
				i++;
			while (*str && *str != ' ')
				str++;
		}
	}
	return (i);
}

void	check_fd(int *fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

t_point	**get_memory(t_map *map)
{
	int	row;

	map->matrix = ft_calloc(map->height, sizeof(t_point));
	if (!map->matrix)
		return (NULL);
	row = 0;
	while (row < map->height)
	{
		map->matrix[row] = ft_calloc(map->width, sizeof(t_point));
		if (!map->matrix[row])
		{
			free_map(map);
			return (NULL);
		}
		row++;
	}
	return (map->matrix);
}

void	free_split(char **nums)
{
	int	i;

	i = 0;
	while (nums[i])
	{
		free(nums[i]);
		i++;
	}
	free(nums);
}

int	set_width_and_height(t_map *map, char *file)
{
	int		fd;
	char	*line;

	check_fd(&fd, file);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), 0);
	map->width = count_words(line);
	if (map->width == 0)
		return (free(line), get_next_line(-5), close(fd), 0);
	map->height = 0;
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
		if (line && (count_words(line) != map->width))
			return (free(line), get_next_line(-5), close(fd), 0);
	}
	return (close(fd), 1);
}
