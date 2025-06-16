/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/04 14:17:04 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	count(t_map *map, char c)
{
	if (c == 'C')
		map->coin += 1;
	if (c == 'E')
		map->hole += 1;
	if (c == 'P')
		map->player += 1;
}

// backtracking to find route to the player
static void	find_route(t_map *map, int x, int y, char **temp)
{
	if (temp[y][x] == 'X')
		return ;
	temp[y][x] = 'X';
	if (map->map[y][x + 1] == 'P' || map->map[y][x - 1] == 'P' || map->map[y
		+ 1][x] == 'P' || map->map[y - 1][x] == 'P')
	{
		map->flag = 0;
		return ;
	}
	if (map->map[y][x + 1] != '1')
		find_route(map, x + 1, y, temp);
	if (map->map[y][x - 1] != '1')
		find_route(map, x - 1, y, temp);
	if (map->map[y + 1][x] != '1')
		find_route(map, x, y + 1, temp);
	if (map->map[y - 1][x] != '1')
		find_route(map, x, y - 1, temp);
}

// check valid path
static void	check_path(t_map *map)
{
	int		x;
	int		y;
	char	**temp;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == 'C' || map->map[y][x] == 'E')
			{
				temp = copy_map(map);
				map->flag = 1;
				find_route(map, x, y, temp);
				ft_free(temp, map->height - 1);
				if (map->flag == 1)
					error(0, -1, map);
			}
			x++;
		}
		y += 1;
	}
	map->hole = 0;
	map->player = 0;
}

// check map and get starting position of player
// check if surrounded by walls
static void	check(t_map *map)
{
	int	x;
	int	y;

	if (map->coin < 1 || map->hole != 1 || map->player != 1)
		error(0, -1, map);
	y = 0;
	while (y < map->height)
	{
		if (map->map[y][0] != '1' || map->map[y][map->width - 1] != '1')
			error(0, -1, map);
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[0][x] != '1' || map->map[map->height - 1][x] != '1')
				error(0, -1, map);
			if (map->map[y][x] == 'P')
			{
				map->x = x;
				map->y = y;
			}
			x++;
		}
		y++;
	}
	check_path(map);
}

// put map details into map struct and check other things
void	parse1(t_map *map, char *input)
{
	int	fd;
	int	x;
	int	y;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		error(2, fd, map);
	y = 0;
	while (y < map->height)
	{
		map->map[y] = get_next_line(fd);
		if (!map->map[y])
			error(4, fd, map);
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			count(map, map->map[y][x]);
			x++;
		}
		y += 1;
	}
	get_next_line(-1);
	close(fd);
	check(map);
}
