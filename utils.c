/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/05 11:31:48 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error(int i, int fd, t_map *map)
{
	if (map)
		ft_free(map->map, map->height - 1);
	if (fd >= 0)
		close(fd);
	if (i == 0)
		ft_printf("Error\nInvalid Map!\n");
	else
		ft_printf("Error\n%s\n", strerror(i));
	get_next_line(-1);
	exit(1);
}

void	die(t_map *map)
{
	int	x;
	int	y;

	put_info(map);
	y = 0;
	while (y < map->height)
	{
		map->y = y;
		x = 0;
		while (x < map->width)
		{
			map->x = x;
			put_dead(map);
			x++;
			map->retry = 1;
		}
		y++;
	}
	mlx_hook(map->win, 2, 1L << 0, finish1, map);
	mlx_loop(map->mlx);
}

int	end(t_map *map)
{
	mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	ft_free(map->map, map->height - 1);
	exit(0);
}

int	finish1(int keycode, t_map *map)
{
	if (keycode == 65307)
		end(map);
	else
	{
		mlx_destroy_window(map->mlx, map->win);
		mlx_destroy_display(map->mlx);
		free(map->mlx);
		ft_free(map->map, map->height - 1);
		start(map, 1, NULL);
	}
	return (0);
}

void	finish(t_map *map)
{
	int	x;
	int	y;

	put_info(map);
	y = 0;
	while (y < map->height)
	{
		map->y = y;
		x = 0;
		while (x < map->width)
		{
			map->x = x;
			put_chicken(map);
			x++;
		}
		y++;
	}
	map->retry = 0;
	mlx_hook(map->win, 2, 1L << 0, finish1, map);
	mlx_loop(map->mlx);
}
