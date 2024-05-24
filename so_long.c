/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:44:33 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:44:35 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// #include
//#include <MLX42/MLX42.h>
//#include "./mlx.h"
#define HEIGHT 600
#define WIDTH 900

void	put_bg(mlx_t *mlx, int j, int i)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png("./pngs/back_grround.png");
	if (!texture)
		game_error(0);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		game_error(0);
	mlx_delete_texture(texture);
	mlx_image_to_window(mlx, img, j * 65, i * 65);
}

int	get_height_width(char **map, int height_or_width_command)
{
	int	i;

	if (height_or_width_command == 1)
	{
		i = 0;
		while (map[i])
			i++;
		return (i);
	}
	else
	{
		return (ft_strlen(map[0]));
	}
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	struct s_long	mx;

	(void)keydata;
	mx = *(struct s_long *)param;
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

void	check_leaks(void)
{
	system("leaks -q Game");
}

void	free_map(struct s_long ml)
{
	int	i;

	i = 0;
	while (ml.map[i])
	{
		free(ml.map[i]);
		i++;
	}
	free(ml.map);
}
void flood_fill(char **map, int y , int x, char c, int *coins_len, int *exit_found)
{
	int height;
	int width;
	
	height = get_height_width(map, 1);
	width = get_height_width(map, 0);
	if (map[y][x] == 'C')
		(*coins_len)--;
	if (map[y][x] == 'E')
		(*exit_found)++;
	if (y < 0 || y >= height || x >= width || x < 0 || map[y][x] == c || map[y][x] == '1')
		{
			//printf("\t\n| Hello world!\n");
			return ;
		}
	map[y][x] = '#';
	flood_fill(map, y+1, x, '#', coins_len, exit_found);
	flood_fill(map, y-1, x, '#', coins_len, exit_found);
	flood_fill(map, y, x+1, '#', coins_len, exit_found);
	flood_fill(map, y, x-1, '#', coins_len, exit_found);
}
int coins_len(char **map)
{
	int i;
	int j;
	int count;
	i =0 ;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int get_player_position(char **map, char c)
{
	int x;
	int y;

	y = 0;
	while (map[y])
	{
		
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				if (c == 'y')
					return (y);
				if (c == 'x')
					return (x);
			}
			x++;
		}
		y++;
	}
	return (0);
}
char ** get_map_from_file(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "[-] Error : invalid file name!", 30);
		exit(1);
	}
	return (mapper(fd));
}
 struct s_long set_struct( char *file_name)
 {
	struct s_long sl;
	sl.map = get_map_from_file(file_name);
	sl.coins_num = coins_len(sl.map);
	sl.exit_found = 0;
	return (sl);
 }
int	main(int argc, char **argv)
{
	struct s_long	ml;
	mlx_t			*mlx;
	atexit(check_leaks);
	if (argc != 2)
	{
		write(2, "[-] Error : cant find map file!", 31);
		return (0);
	}
	ml = set_struct(argv[1]);
	flood_fill(ml.map, get_player_position(ml.map, 'y'), get_player_position(ml.map, 'x'), '#', &ml.coins_num, &ml.exit_found);
	if (ml.coins_num || !ml.exit_found)
	 	game_error(1);
	free_map(ml);
	ml.map = get_map_from_file(argv[1]);
	int i, j;
	i = 0;
	while (ml.map[i])
	{
		j = 0;
		while (ml.map[i][j])
		{
			printf("%c", ml.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	check_map(ml.map);
	mlx = mlx_init(get_height_width(ml.map, 0) * 65, get_height_width(ml.map, 1)
			* 65, "so long", false);
	if (!mlx)
		game_error(0);
	ml.mlx = mlx;
	ml.imgg = set_game(&ml);
	mlx_key_hook(mlx, ft_hook, &ml);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	mlx_delete_image(ml.mlx, ml.imgg);
	free_map(ml);
	atexit(check_leaks);
	//system("leaks -q Game");	
	return (0);
}
