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
};
int ft_strlen(char const *s);
int check_map(char **map);
#endif