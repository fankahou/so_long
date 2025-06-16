/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:25 by kfan              #+#    #+#             */
/*   Updated: 2024/11/05 12:18:33 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check if file ends with .ber
void	ft_file(t_map *map, int argc, char *input)
{
	int			len;
	static int	level;

	if (argc == 1 && map->retry == 0)
	{
		level++;
		ft_strlcpy(map->path, "maps/1.ber", 11);
		map->path[5] = level + '0';
	}
	else if (map->retry == 0)
		ft_strlcpy(map->path, input, ft_strlen(input) + 1);
	len = ft_strlen(map->path);
	if (len < 5)
		error(0, -1, NULL);
	if (!(map->path[len - 1] == 'r' && map->path[len - 2] == 'e'
			&& map->path[len - 3] == 'b' && map->path[len - 4] == '.'))
		error(0, -1, NULL);
}

void	init_img(t_map *map, t_img *img, char *path)
{
	if (map->scale == 64)
		ft_strlcpy(img->path, "textures/64/", 13);
	if (map->scale == 32)
		ft_strlcpy(img->path, "textures/32/", 13);
	if (map->scale == 16)
		ft_strlcpy(img->path, "textures/16/", 13);
	ft_strlcpy(&img->path[12], path, ft_strlen(path) + 1);
	img->img = mlx_xpm_file_to_image(map->mlx, img->path, &img->width,
			&img->height);
	if (!img->img)
		put_error(map, "Cannot load xpm file");
}

// energy will be put at the furthest corner from player
void	init_enermy(t_map *map)
{
	if (map->x > map->width / 2)
	{
		map->flag1 = 0;
		map->xy[0] = 1;
	}
	else
	{
		map->flag1 = 1;
		map->xy[0] = map->width - 2;
	}
	if (map->y > map->height / 2)
		map->xy[1] = 1;
	else
		map->xy[1] = map->height - 2;
	map->enermy = 0;
}

static void	check_screen(t_map *map)
{
	int	x;
	int	y;

	map->mlx = mlx_init();
	if (!map->mlx)
		error(4, -1, map);
	mlx_get_screen_size(map->mlx, &x, &y);
	map->scale = 64;
	while (map->width * map->scale > x || (map->height + 1) * map->scale > y)
		map->scale /= 2;
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	if (map->scale < 8)
		error(0, -1, map);
}

// initilize and open window
void	init(t_map *map)
{
	check_screen(map);
	map->mlx = mlx_init();
	if (!map->mlx)
		error(4, -1, map);
	map->win = mlx_new_window(map->mlx, map->width * map->scale, (map->height
				+ 1) * map->scale, "so_long");
	if (!map->win)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
		error(4, -1, map);
	}
}
