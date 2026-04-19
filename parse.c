/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/04 13:42:03 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		array[i] = NULL;
		i--;
	}
	free(array);
	array = NULL;
}

static int	checkchar(char c)
{
	if (c != '1' && c != '0' && c != 'C' && c != 'P' && c != 'E')
		return (1);
	return (0);
}

// get y and check if it's a rectangal
// check also map consists only the 5 char
void	parse(t_map *map, char *input)
{
	int		fd;
	char	*temp;
	int		x;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		error(2, fd, NULL);
	map->width = 0;
	map->height = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		x = 0;
		while (temp[x] && temp[x] != '\n' && !checkchar(temp[x]))
			x++;
		free(temp);
		if (map->width != x && map->height != 0)
			error(0, fd, NULL);
		map->height += 1;
		map->width = x;
	}
	close(fd);
}

// make a copy of temp map for backtracking
char	**copy_map(t_map *map)
{
	char	**temp;
	int		y;

	temp = calloc((map->height + 1), sizeof(void *));
	if (!temp)
		error(12, -1, map);
	y = 0;
	while (y < map->height)
	{
		temp[y] = ft_strdup(map->map[y]);
		if (!temp[y])
			error(12, -1, map);
		y++;
	}
	return (temp);
}
