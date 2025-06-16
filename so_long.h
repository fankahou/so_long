/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfan <kfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:00:37 by kfan              #+#    #+#             */
/*   Updated: 2024/11/04 13:51:41 by kfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <string.h>

typedef struct s_map
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		x;
	int		y;
	int		coin;
	int		hole;
	int		player;
	int		flag;
	int		flag1;
	int		enermy;
	int		retry;
	int		scale;
	int		xy[2];
	char	path[100];
}			t_map;

typedef struct s_img
{
	void	*img;
	char	path[22];
	int		width;
	int		height;
}			t_img;

void		ft_free(char **array, int i);
void		error(int i, int fd, t_map *map);
char		**copy_map(t_map *map);
void		parse(t_map *map, char *input);
void		parse1(t_map *map, char *input);
int			end(t_map *map);
int			finish1(int keycode, t_map *map);
void		finish(t_map *map);
int			put_chicken(t_map *map);
int			put_chicken_mirror(t_map *map);
void		put_num(t_map *map, char *input, int position, char flag);
void		put_hole(t_map *map);
void		put_map(t_map *map);
void		put_info(t_map *map);
void		init_img(t_map *map, t_img *img, char *path);
void		init(t_map *map);
void		put_enermy(t_map *map);
void		put_enermy_mirror(t_map *map);
void		put_dead(t_map *map);
void		die(t_map *map);
void		move_enermy(t_map *map);
void		init_enermy(t_map *map);
void		put_error(t_map *map, char *message);
void		put_cover(t_map *map, int x, int y);
void		ft_file(t_map *map, int argc, char *input);
void		start(t_map *map, int argc, char *input);

#endif