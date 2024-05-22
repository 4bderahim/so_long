#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "MLX42.h"
#include <errno.h>
#include <string.h>
#ifndef SO_LONG
#define SO_LONG

struct s_long
{
    mlx_t *mlx;
    char **map;
    mlx_image_t* imgg;
    int32_t cu_y;
    int32_t cu_x;
};
int ft_strlen(char const *s);
int check_map(char **map);
mlx_image_t *set_game(struct s_long *ml);
mlx_image_t *put_the_cat(mlx_t *mlx, int j, int i);
void put_bg( mlx_t *mlx, int j, int i);
void put_exit( mlx_t *mlx, int j, int i);
mlx_image_t *put_player(char **map, mlx_t *mlx);
void put_walls(mlx_t *mlx,struct s_long mx);
void game_error(int err_flag);
#endif