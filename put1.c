/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/01 21:23:47 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_error(t_map *map, char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	ft_free(map->map, map->height - 1);
	exit(1);
}

// sleep?
int	put_chicken(t_map *map)
{
	t_img	chicken1;
	t_img	chicken2;

	if (map->flag1 == 0)
		put_enermy(map);
	else
		put_enermy_mirror(map);
	init_img(map, &chicken1, "idle1.xpm");
	init_img(map, &chicken2, "idle2.xpm");
	if (mlx_put_image_to_window(map->mlx, map->win, chicken1.img, map->x
			* map->scale, map->y * map->scale) < 0)
		put_error(map, "Cannot put chicken info to win");
	if (mlx_put_image_to_window(map->mlx, map->win, chicken2.img, map->x
			* map->scale, map->y * map->scale) < 0)
		put_error(map, "Cannot put chicken info to win");
	mlx_destroy_image(map->mlx, chicken1.img);
	mlx_destroy_image(map->mlx, chicken2.img);
	return (0);
}

int	put_chicken_mirror(t_map *map)
{
	t_img	chicken1;
	t_img	chicken2;

	if (map->flag1 == 0)
		put_enermy(map);
	else
		put_enermy_mirror(map);
	init_img(map, &chicken1, "idle3.xpm");
	init_img(map, &chicken2, "idle4.xpm");
	if (mlx_put_image_to_window(map->mlx, map->win, chicken1.img, map->x
			* map->scale, map->y * map->scale) < 0)
		put_error(map, "Cannot put chicken info to win");
	if (mlx_put_image_to_window(map->mlx, map->win, chicken2.img, map->x
			* map->scale, map->y * map->scale) < 0)
		put_error(map, "Cannot put chicken info to win");
	mlx_destroy_image(map->mlx, chicken1.img);
	mlx_destroy_image(map->mlx, chicken2.img);
	return (0);
}

void	put_cover(t_map *map, int x, int y)
{
	void	*cover;

	cover = mlx_new_image(map->mlx, map->scale, map->scale);
	if (!cover)
		put_error(map, "Cannot make cover");
	if (mlx_put_image_to_window(map->mlx, map->win, cover, x * map->scale, y
			* map->scale) < 0)
		put_error(map, "Cannot put img to win");
	mlx_destroy_image(map->mlx, cover);
}

void	put_num(t_map *map, char *input, int position, char flag)
{
	t_img	num;
	char	temp[6];
	int		i;

	i = ft_digit(map->player);
	if (flag == 'c')
		i = ft_digit(map->hole);
	while (i > 0)
	{
		if (flag == 'm')
			temp[0] = input[ft_digit(map->player) - i];
		if (flag == 'c')
			temp[0] = input[i - 1];
		ft_strlcpy(&temp[1], ".xpm", 5);
		init_img(map, &num, temp);
		if (mlx_put_image_to_window(map->mlx, map->win, num.img, position
				* map->scale, map->height * map->scale) < 0)
			put_error(map, "Cannot put num to win");
		mlx_destroy_image(map->mlx, num.img);
		i--;
		if (flag == 'm')
			position++;
		if (flag == 'c')
			position--;
	}
}
