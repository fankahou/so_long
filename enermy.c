/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enermy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:02:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/01 21:33:40 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_enermy(t_map *map)
{
	t_img	duck1;
	t_img	duck2;
	int		x;
	int		y;

	x = map->xy[0];
	y = map->xy[1];
	init_img(map, &duck1, "duck1.xpm");
	init_img(map, &duck2, "duck2.xpm");
	if (mlx_put_image_to_window(map->mlx, map->win, duck1.img, map->xy[0]
			* map->scale, map->xy[1] * map->scale) < 0)
		put_error(map, "Cannot put enermy info to win");
	if (mlx_put_image_to_window(map->mlx, map->win, duck2.img, map->xy[0]
			* map->scale, map->xy[1] * map->scale) < 0)
		put_error(map, "Cannot put enermy info to win");
	mlx_destroy_image(map->mlx, duck1.img);
	mlx_destroy_image(map->mlx, duck2.img);
}

void	put_enermy_mirror(t_map *map)
{
	t_img	duck1;
	t_img	duck2;
	int		x;
	int		y;

	x = map->xy[0];
	y = map->xy[1];
	init_img(map, &duck1, "duck3.xpm");
	init_img(map, &duck2, "duck4.xpm");
	if (mlx_put_image_to_window(map->mlx, map->win, duck1.img, map->xy[0]
			* map->scale, map->xy[1] * map->scale) < 0)
		put_error(map, "Cannot put enermy info to win");
	if (mlx_put_image_to_window(map->mlx, map->win, duck2.img, map->xy[0]
			* map->scale, map->xy[1] * map->scale) < 0)
		put_error(map, "Cannot put enermy info to win");
	mlx_destroy_image(map->mlx, duck1.img);
	mlx_destroy_image(map->mlx, duck2.img);
}

void	put_dead(t_map *map)
{
	t_img	dead;

	init_img(map, &dead, "dead.xpm");
	if (mlx_put_image_to_window(map->mlx, map->win, dead.img, map->x
			* map->scale, map->y * map->scale) < 0)
		put_error(map, "Cannot put dead chicken info to win");
	mlx_destroy_image(map->mlx, dead.img);
}

static void	change_direction(t_map *map, int x, int new)
{
	if (x < new)
		map->flag1 = 0;
	if (x > new)
		map->flag1 = 1;
}

// enermy can go through wall once every 10 moves
void	move_enermy(t_map *map)
{
	int	x;
	int	y;
	int	flag;

	x = map->xy[0];
	y = map->xy[1];
	flag = 0;
	if (map->player % 10 == 0)
		flag = 1;
	if (x < map->x && (map->map[y][x + 1] != '1' || flag == 1) && !(y == map->y
			&& x + 1 == map->x))
		map->xy[0] += 1;
	else if (x >= map->x && (map->map[y][x - 1] != '1' || flag == 1)
		&& !(y == map->y && x - 1 == map->x))
		map->xy[0] -= 1;
	else if (y < map->y && (map->map[y + 1][x] != '1' || flag == 1) && !(y
			+ 1 == map->y && x == map->x))
		map->xy[1] += 1;
	else if (y >= map->y && (map->map[y - 1][x] != '1' || flag == 1) && !(y
			- 1 == map->y && x == map->x))
		map->xy[1] -= 1;
	if (x != map->xy[0] || y != map->xy[1])
		put_cover(map, x, y);
	change_direction(map, x, map->xy[0]);
	put_map(map);
}
