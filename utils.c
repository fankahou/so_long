#include "so_long.h"

void    error(int i, int fd, t_map *map)
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
    
#ifndef __EMSCRIPTEN__
    exit(1); // Only exit natively, WebGL will just freeze here
#endif
}

void    die(t_map *map)
{
    int x;
    int y;

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
    // Change keyboard listener to the restart/exit function
    mlx_hook(map->win, 2, 1L << 0, finish1, map);
    // Freeze the game animation
    mlx_loop_hook(map->mlx, NULL, NULL); 
}

void    die1(t_map *map)
{
    int x;
    int y;

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
            map->retry = 1;
        }
        y++;
    }
    // Change keyboard listener to the restart/exit function
    mlx_hook(map->win, 2, 1L << 0, finish1, map);
    // Freeze the game animation
    mlx_loop_hook(map->mlx, NULL, NULL); 
}

int end(t_map *map)
{
    // mlx_destroy_window safely cancels the Emscripten loop now
    mlx_destroy_window(map->mlx, map->win);
    //mlx_destroy_display(map->mlx);
    free(map->mlx);
    ft_free(map->map, map->height - 1);

#ifndef __EMSCRIPTEN__
    exit(0); // Only exit completely on desktop
#endif
    return (0);
}

int finish1(int keycode, t_map *map)
{
    // 27 is ESC on both Mac and Web
    if (keycode == 27)
        end(map);
    // 13 is W on Mac, 119 is W on Web (Update this if needed!)
    else if (keycode == 13 || keycode == 119)
    {
        mlx_destroy_window(map->mlx, map->win);
        //mlx_destroy_display(map->mlx);
        free(map->mlx);
        ft_free(map->map, map->height - 1);
        start(map, 1, NULL); // Restart the game
    }
    return (0);
}

void    finish(t_map *map)
{
    int x;
    int y;

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
    // Change keyboard listener to the restart/exit function
    mlx_hook(map->win, 2, 1L << 0, finish1, map);
    // Freeze the game animation
    mlx_loop_hook(map->mlx, NULL, NULL); 
}

void    finishe(t_map *map)
{
    int x;
    int y;

    put_info(map);
    y = 0;
    while (y < map->height)
    {
        map->xy[1] = y;
        x = 0;
        while (x < map->width)
        {
            map->xy[0] = x;
            put_enermy(map);
            x++;
        }
        y++;
    }
    map->retry = 0;
    // Change keyboard listener to the restart/exit function
    mlx_hook(map->win, 2, 1L << 0, finish1, map);
    // Freeze the game animation
    mlx_loop_hook(map->mlx, NULL, NULL); 
}