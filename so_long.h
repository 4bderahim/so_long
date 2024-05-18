#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "MLX42.h"
#ifndef SO_LONG
#define SO_LONG


struct s_long
{
    mlx_t *mlx;
    char **map;
    mlx_image_t** imgg;
};
int ft_strlen(char const *s);
int check_map(char **map);
void set_game(struct s_long ml);
mlx_image_t *put_the_cat(mlx_t *mlx, int j, int i);
void pt_bg( mlx_t *mlx, int j, int i);
void put_exit( mlx_t *mlx, int j, int i);
#endif