#include "so_long.h"
// #include 
#include <MLX42/MLX42.h>
//#include "./mlx.h"
#define HEIGHT 600
#define WIDTH 900
static char** map;

static mlx_image_t* imgg;
int ft_strlen(char const *s)
{
    int i ;
    i = 0;
    while (s[i])
        {
            i++;
        }
    return (i);
}
void	*ft_calloc(size_t count, size_t size)
{
	char	*all;
	size_t	tmp;
    size_t i;
	if (count == 0 || size == 0)
	{
		all = (char *)malloc(count * size);
        all[0] = 0;
		return (all);
	}
	tmp = count * size;
	if ((tmp / size) != count)
		return (NULL);
	all = (char *)malloc(count * size);
	if (!all)
		return (NULL);
    i = 0;
    while (i < count*size)
    {
        all[i] = 0;
        i++;
    }
	return (all);
}

void	join_the_two_strings(char *all, char const *s1, char const *s2)
{
	size_t	i;
	int		j;

	i = 0;
	while (s1[i])
	{
		all[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		all[i] = s2[j];
		i++;
		j++;
	}
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*allocated;
	size_t	string_len;

	if (!s1 || !s1)
		return (NULL);
	string_len = ft_strlen(s1) + ft_strlen(s2);
	allocated = (char *)malloc(string_len + 1);
	if (!allocated)
		return (NULL);
	join_the_two_strings(allocated, s1, s2);
	allocated[string_len] = '\0';
    free(s1);
	return (allocated);
}
char *map_reader(int fd)
{
    char *sp;
    char *map;
    int c;
    map = (char *) malloc(1);
    if (!map)
        return (NULL);
    map[0] = 0;
    c = 1;
    while (c != 0)
    {
        sp = (char *) ft_calloc(101,1);
        if (!sp)
            return (NULL);
        c = read(fd, sp, 100);
        if (c == -1)
            exit(0);
        map = ft_strjoin(map, sp);
        free(sp);
    }
    return (map);
}
int count_map_hpaths(char *s)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] != '\n' && (s[i+1] == '\0' || s[i+1] == '\n'))
            count++;
        i++;
    }
    return (count);
}
void join_to_map(char **sp,char *s, int ii, int index)
{

    int i;
    i = 0;  

    if (ii != 0)
        ii++;
    s = s+ii;
    while (s[i] != '\0' && s[i] != '\n')
        i++;
    sp[index] = (char *) malloc(i+1);
    if (!sp[index])
        return ;
    sp[index][i] = 0;
    i = 0;
    while (s[i] !=0 && s[i] != '\n')
    {
        sp[index][i] = s[i];
        i++;
    }
}
char **mapper(int fd)
{
    char *map_full_road;
    char **spilited_map;
    int i;
    int index;

    index = 0;
    i = 0;
    map_full_road = map_reader(fd);
    if (!map_full_road)
        exit(0);
    spilited_map = (char **) malloc(sizeof(char *)*(count_map_hpaths(map_full_road)+1));
    spilited_map[count_map_hpaths(map_full_road)] = NULL;
    while (map_full_road[i])
    {
        if (map_full_road[i] == '\n' || i == 0)
            {
                join_to_map(spilited_map,map_full_road,i, index);
                index++;
            }
        i++;
    }
    free(map_full_road);
    return(spilited_map);
}
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;
//     mlx_texture_t* texture = mlx_load_png("./dawg_flip.png");
//     mlx_image_t* img = mlx_texture_to_image(mlx, texture);
//     mlx_image_to_window(mlx, img, j*65, i*65); 

//     mlx_texture_t* texture1 = mlx_load_png("./dawg_flip_flip.png");
//     mlx_image_t* img1 = mlx_texture_to_image(mlx, texture1);
//     mlx_image_to_window(mlx, img1, j*65, i*65);
// 	//printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }
void put_zrbya( mlx_t *mlx, int j, int i)
{
    mlx_texture_t* texture = mlx_load_png("./carpet.png");
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    if (mlx_image_to_window(mlx, img, j*65, i*65) == -1) 
    {
        printf("\t\t\tHelo \n\tworld");
    }
}

void put_exit( mlx_t *mlx, int j, int i)
{
    mlx_texture_t* texture = mlx_load_png("./exit_cat.png");
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    mlx_image_to_window(mlx, img, j*65, i*65); 
    
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
// void put_the_dog( mlx_t *mlx, int j, int i)
// {
//     mlx_texture_t* texture = mlx_load_png("./dawg.png");
//     mlx_image_t* img = mlx_texture_to_image(mlx, texture);
//     mlx_image_to_window(mlx, img, j*65, i*65); 
    
// }
void put_collectibles(char **map, mlx_t *mlx)
{
    int i;
    int j;
    i = 0;
    
    mlx_texture_t* texture = mlx_load_png("./fisher.png");
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
mlx_image_t *put_the_cat(mlx_t *mlx, int j, int i)
{
    
    mlx_texture_t* texture = mlx_load_png("./caat.png");
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    mlx_image_to_window(mlx,img, j*65, i*65);
    return (img);

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
            // if (map[i][j] == 'E')
            // {
            //     put_the_dog(mlx, j, i);
            // }
            if (map[i][j] == 'P')
                {
                    return (put_the_cat(mlx, j, i));
                }
            
            j++;
        }
        i++;
    }
    return (NULL);
}

void put_walls(char **map, mlx_t **mlxx)
{
    int i;
    int j;
    i = 0;
    mlx_t *mlx;

    mlx = *mlxx;
    mlx_texture_t* texture = mlx_load_png("./box.png");
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            put_zrbya(mlx, j, i);
            if (map[i][j] == '1')
                {
                    mlx_image_to_window(mlx, img, j*65, i*65);
                }
            j++;
        }
        i++;
    }
}


int get_height_width(char **map, int height_or_width_command)
{
    int i;
    
    if (height_or_width_command == 1)
        {
            i = 0;
            while (map[i])
            {
                i++;
            }
            printf("\t%d>\n", i);
            return (i);
        }
    else
    {
        printf("\t[%d]\n", ft_strlen(map[0]));
        return (ft_strlen(map[0]));
    }
    
}
void put_the_dog__( mlx_t *mlx, int j, int i)
{
    
    
    // mlx_texture_t* texture = mlx_load_png("./dawg.png");
    // mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    // mlx_image_to_window(mlx, img, j*65, i*65); 
    mlx_texture_t* texture1 = mlx_load_png("./dawg_flip.png");
    mlx_image_t* img1 = mlx_texture_to_image(mlx, texture1);
    
    mlx_image_to_window(mlx, img1, j*65, i*65);
    printf("%d||%d\n\n", j,i);
    
}
int go_down(mlx_t *mlx, char **map)
{

    int i;
    int j;
    i = 0;
    
    //mlx_t *mlx = param;
   
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            
            if (map[i][j] == 'p')
            {
                return (i);
            }
            j++;
        }
        i++;
    }
    return (0);
}
void change_p(char **map)
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
                map[i][j] = '0';
            j++;
        }
        i++;
    }
}
void set_game(struct s_long ml)
{
    put_walls(ml.map, &ml.mlx);
    put_collectibles(ml.map, ml.mlx);
    
    imgg = put_player(ml.map, ml.mlx);
    put_the_exit(ml.map, ml.mlx);
}
int check_collect(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'C')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}
int move_the_player(struct s_long mx, mlx_image_t *imgg, int y, int x)
{
    if(mx.map[y][x] == '1')
        return (0);
    if(mx.map[y][x] == 'C')
    {
        change_p(mx.map);
        mx.map[y][x] = 'P';
        set_game(mx);    
    }
    if (mx.map[y][x] == 'E')
        {
            if (!check_collect(mx.map))
            {
                set_game(mx);  
                change_p(mx.map);
                mlx_close_window(mx.mlx);
            }
        }
   

    return (1);
}
void apply_key(struct s_long mx, mlx_image_t *imgg, int direction)
{
    int y;
    int  x;
    char next_position;

    if (direction == 1 || direction == 3)
        {
            if (direction == 1)
                y = (imgg->instances[0].y / 65) - 1;
            else
                y = (imgg->instances[0].y / 65) + 1;
            if (move_the_player(mx, imgg, y, imgg->instances[0].x / 65))
                {
                    if (direction == 1)
                        imgg->instances[0].y -= 65;
                    else
                        imgg->instances[0].y += 65;
                } 
            return ;
        }
    if (direction == 4)
        x = (imgg->instances[0].x / 65) - 1;
    else
        x = (imgg->instances[0].x / 65) + 1;
    if (move_the_player(mx, imgg,imgg->instances[0].y / 65, x))
    {
        if (direction == 4)
            imgg->instances[0].x -= 65;
        else
            imgg->instances[0].x += 65;
    }
}
static void ft_hook(mlx_key_data_t keydata, void * param)
{
    struct s_long mx;
    
    mx = *(struct s_long*)param;
    
    if (mlx_is_key_down(mx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mx.mlx);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_UP))
		{
            apply_key(mx, imgg,1);
        }
    else if (mlx_is_key_down(mx.mlx, MLX_KEY_RIGHT))
    {
        apply_key(mx, imgg,2);
    }
    else if (mlx_is_key_down(mx.mlx, MLX_KEY_LEFT))
    {
        apply_key(mx, imgg,4);
    }
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_DOWN))
    {
        apply_key(mx, imgg,3);
    }
    usleep(1000);
}

int main()
{
    int fd;
    char **map;
    fd = open("map.ber", O_RDONLY);
    if (!fd)
        return (0);
    map = mapper(fd);
    check_map(map);
    fd = 0;
    while (map[fd])
        {
            printf("%s\n", map[fd]);
            fd++;
        }
    if (!map)
        return (0);
    
    //mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(get_height_width(map, 0)*65, get_height_width(map, 1)*65, "a title", false);
    if (!mlx)
		ft_error();
        
    struct s_long ml;
    ml.map = map;
    ml.mlx = mlx;

    set_game(ml);
    mlx_key_hook(mlx, ft_hook, &ml);
   // mlx_loop_hook(mlx, my_keyhook, &mlx);
	mlx_loop(mlx);
    
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
    
    // system("leaks -q a.out");
    // return (0);

}
