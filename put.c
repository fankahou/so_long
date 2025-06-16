/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/04 13:56:00 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_info(t_map *map)
{
	t_img	info1;
	t_img	info2;
	char	*move;
	char	*coin;

	move = ft_itoa(map->player);
	coin = ft_itoa(map->hole);
	if (map->enermy == 1)
		init_img(map, &info1, "duck1.xpm");
	else
		init_img(map, &info1, "idle1.xpm");
	init_img(map, &info2, "coin.xpm");
	if (mlx_put_image_to_window(map->mlx, map->win, info1.img, 0, map->height
			* map->scale) < 0)
		put_error(map, "Cannot put move info to win");
	if (mlx_put_image_to_window(map->mlx, map->win, info2.img, (map->width - 1
				- ft_digit(map->hole)) * map->scale, map->height
			* map->scale) < 0)
		put_error(map, "Cannot put coin info to win");
	mlx_destroy_image(map->mlx, info1.img);
	mlx_destroy_image(map->mlx, info2.img);
	put_num(map, move, 1, 'm');
	put_num(map, coin, map->width - 1, 'c');
	free(move);
	free(coin);
}

void	put_hole(t_map *map)
{
	t_img	hole;
	int		x;
	int		y;

	init_img(map, &hole, "hole.xpm");
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == 'E')
				if (mlx_put_image_to_window(map->mlx, map->win, hole.img, x
						* map->scale, y * map->scale) < 0)
					put_error(map, "Cannot put hole to win");
			x++;
		}
		y++;
	}
	mlx_destroy_image(map->mlx, hole.img);
}

static void	put_wall(t_map *map)
{
	t_img	wall;
	int		x;
	int		y;

	init_img(map, &wall, "wall.xpm");
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == '1')
				if (mlx_put_image_to_window(map->mlx, map->win, wall.img, x
						* map->scale, y * map->scale) < 0)
					put_error(map, "Cannot put wall to win");
			x++;
		}
		y++;
	}
	mlx_destroy_image(map->mlx, wall.img);
}

static void	put_coin(t_map *map)
{
	t_img	coin;
	int		x;
	int		y;

	init_img(map, &coin, "coin.xpm");
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == 'C')
				if (mlx_put_image_to_window(map->mlx, map->win, coin.img, x
						* map->scale, y * map->scale) < 0)
					put_error(map, "Cannot put coin to win");
			x++;
		}
		y++;
	}
	mlx_destroy_image(map->mlx, coin.img);
}

// put items into window
void	put_map(t_map *map)
{
	put_coin(map);
	put_wall(map);
}
