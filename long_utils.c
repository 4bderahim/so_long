#include "so_long.h"



void put_bg( mlx_t *mlx, int j, int i)
{
    mlx_texture_t* texture = mlx_load_png("./pngs/back_grround.png");
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    if (mlx_image_to_window(mlx, img, j*65, i*65) == -1) 
    {
        printf("[-] Error!\n");
    }
}

mlx_image_t *put_the_exit(char **map, mlx_t *mlx)
{
    int i;
    int j;
    i = 0;
    
   
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            // if (map[i][j] == 'E')
            // {
            //     put_the_dog(mlx, j, i);
            // }
            if (map[i][j] == 'E')
                {
                    put_exit(mlx, j, i);
                }
            
            j++;
        }
        i++;
    }
    return (NULL);
}
void put_walls(mlx_t *mlx,struct s_long mx)
{
    int i;
    int j;
    i = 0;
    mlx_image_t* img;
    if (mlx == NULL )
        printf("@+@+\n\n\n\n");
    mlx_texture_t* texture = mlx_load_png("./pngs/box.png");
    printf("#->\n\n\n");
    img = mlx_texture_to_image(mlx, texture);
        

    while (mx.map[i])
    {
        j = 0;
        while (mx.map[i][j])
        {
            put_bg(mx.mlx, j, i);
            if (mx.map[i][j] == '1')
                {
                    mlx_image_to_window(mx.mlx, img, j*65, i*65);
                }
            j++;
        }
        i++;
    }
    
}

void put_collectibles(char **map, mlx_t *mlx)
{
    int i;
    int j;
    i = 0;
    
    mlx_texture_t* texture = mlx_load_png("./pngs/fish.png");
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'C')
                {
                    mlx_image_to_window(mlx, img, j*65, i*65);
                }
            j++;
        }
        i++;
    }
}


mlx_image_t *put_player(char **map, mlx_t *mlx)
{
    int i;
    int j;
    i = 0;
    
   
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
                {
                    return ((put_the_cat(mlx, j, i)));
                }
            
            j++;
        }
        i++;
    }
    
    return (NULL);
}

mlx_image_t *set_game(struct s_long *ml)
{
    mlx_image_t* img;
    put_walls(ml->mlx, *ml);
    printf("\t\t[!#]\n");
    ml->imgg  = put_player(ml->map, ml->mlx);
    put_collectibles(ml->map, ml->mlx);
    put_the_exit(ml->map, ml->mlx);
    
    return (ml->imgg);
    
}