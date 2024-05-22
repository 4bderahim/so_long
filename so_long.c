#include "so_long.h"
// #include 
//#include <MLX42/MLX42.h>
//#include "./mlx.h"
#define HEIGHT 600
#define WIDTH 900



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


void put_exit( mlx_t *mlx, int j, int i)
{
    mlx_texture_t* texture = mlx_load_png("./pngs/exit_door.png");
    if (!texture)
        game_error();
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    if (!img)   
        game_error();
    mlx_delete_texture(texture);
    mlx_image_to_window(mlx, img, j*65, i*65);    
}

mlx_image_t *put_the_cat(mlx_t *mlx, int j, int i)
{
    mlx_texture_t* texture = mlx_load_png("./pngs/caat.png");
    if (!texture)
        game_error();
    mlx_image_t* img = mlx_texture_to_image(mlx, texture);
    if (!img)
        game_error();
    mlx_image_to_window(mlx,img, j*65, i*65);
    mlx_delete_texture(texture);
    return (img);
}

int get_height_width(char **map, int height_or_width_command)
{
    int i;
    
    if (height_or_width_command == 1)
        {
            i = 0;
            while (map[i])
                i++;
            printf("\t%d>\n", i);
            return (i);
        }
    else
    {
        printf("\t[%d]\n", ft_strlen(map[0]));
        return (ft_strlen(map[0]));
    }
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

void next_step(struct s_long *l,int direction)
{
    struct s_long ll;
    int x;
    int y;

    ll = *l;
    if (direction == 1)
        ll.imgg->instances[0].y = ll.cu_y - 65;
     if (direction == 3)
        ll.imgg->instances[0].y = ll.cu_y + 65 ;
     if (direction == 2)
        ll.imgg->instances[0].x = ll.cu_x + 65;
     if (direction == 4)
        ll.imgg->instances[0].x = ll.cu_x - 65;
    if (ll.map[ll.cu_y/65][ll.cu_x/65] == 'E')
        ll.map[ll.cu_y/65][ll.cu_x/65] = 'E';
    else
        ll.map[ll.cu_y/65][ll.cu_x/65] = '0';
    int i,j;
    i = 0;
    while (ll.map[i])
    {
        j= 0 ;
        while (ll.map[i][j])
        {
            printf("%c", ll.map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    if (ll.map[ll.cu_y/65][ll.cu_x/65] != 'E')
        put_bg(ll.mlx, ll.cu_x/65, ll.cu_y/65);
    *l = ll;
}

int32_t get_x_y(mlx_image_t *img_ins,int direction,  char order)
{
    int32_t x;
    int32_t y;
    y = img_ins->instances[0].y / 65;
    x = img_ins->instances[0].x / 65;
    if (direction == 1 || direction == 3)
    {
        if (direction == 3)
            y += 1;
        if (direction == 1)
            y -= 1;
    }
    else
    {
        if (direction == 2)
            x += 1;
        if (direction == 4)
            x -= 1;
    }
    if (order == 'y')
        return (y);
    return (x);
} 
void move_the_player(struct s_long *mx, int  direction)
{
    struct s_long mlx;
    int32_t y;
    int32_t x;

    mlx = *mx;
    mlx.cu_x = mlx.imgg->instances[0].x;
    mlx.cu_y = mlx.imgg->instances[0].y;
    y = get_x_y(mlx.imgg, direction, 'y');
    x = get_x_y(mlx.imgg, direction, 'x');
    if(mlx.map[y][x] == '1')
        return ;
    if(mlx.map[y][x] == 'C')
        put_bg(mlx.mlx, x, y);
    if (mlx.map[y][x] == 'E')
        {
            if (!check_collect(mlx.map))
                mlx_close_window(mlx.mlx);
            mlx.map[y][x] = 'E';
        }
    else
        mlx.map[y][x] = 'P';
    next_step(&mlx, direction);
    if (mlx.map[y][x] != 'E')
        mlx.imgg = put_the_cat(mlx.mlx, x, y);
    *mx = mlx;
}
static void ft_hook(mlx_key_data_t keydata, void * param)
{
    struct s_long mx;
    
    mx = *(struct s_long*)param;

    if (mlx_is_key_down(mx.mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mx.mlx);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_UP))
		move_the_player(&mx, 1);
    else if (mlx_is_key_down(mx.mlx, MLX_KEY_RIGHT))
        move_the_player(&mx, 2);
    else if (mlx_is_key_down(mx.mlx, MLX_KEY_LEFT))
        move_the_player(&mx, 4);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_DOWN))
        move_the_player(&mx, 3);
}

void check_leaks()
{
    system("leaks -q Game");
}

int main()
{
    int fd;
    char **map;
    
    fd = open("map.ber", O_RDONLY);
    if (!fd)
        return (0);
    map = mapper(fd);
    if (!map)
        return (0);
    check_map(map);
    fd = 0;
    while (map[fd])
        {
            printf("%s\n", map[fd]);
            fd++;
        }
	mlx_t* mlx = mlx_init(get_height_width(map, 0)*65, get_height_width(map, 1)*65, "a title", false);
    if (!mlx)
		game_error();
    struct s_long ml;
    ml.map = map;
    ml.mlx = mlx;
    ml.imgg = set_game(&ml);

    mlx_key_hook(mlx, ft_hook, &ml);
    mlx_loop(mlx);
    mlx_terminate(mlx);
	// return (EXIT_SUCCESS);
    mlx_delete_image(ml.mlx, ml.imgg);
    int i;
    i = 0;
    while (ml.map[i])
    {
        free(ml.map[i]);
        i++;
    }
    free(ml.map);
    system("leaks -q a.out");
    atexit(check_leaks);
    // return (0);
}
