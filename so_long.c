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
		printf("\t%d>\n", i);
		return (i);
	}
	else
	{
		printf("\t[%d]\n", ft_strlen(map[0]));
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
int flood_fill(struct s_long st, int y , int x, char c)
{
	int height;
	int width;

	int i, j;
	i = 0;
	while (st.map[i])
	{
		j = 0;
		while (st.map[i][j])
		{
			printf("%c", st.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	height = get_height_width(st.map, 1);
	width = get_height_width(st.map, 0);
	if (y < 0 || y > height || x > width || x < 0 || st.map[y][x] == c || st.map[y][x] == '1')
		return (0);
	if (st.map[y][x] == 'C')
		return (1);
	st.map[y][x] = '#';
	if (flood_fill(st, y+1, x, '#'))
		return (1);
	if (flood_fill(st, y-1, x, '#'))
		return (1);
	if (flood_fill(st, y, x+1, '#'))
		return (1);
	if (flood_fill(st, y+1, x-1, '#'))
		return (1);
	return (0);
	
}
int	main(int argc, char **argv)
{
	int				fd;
	struct s_long	ml;
	mlx_t			*mlx;

	atexit(check_leaks);
	if (argc != 2)
	{
		write(2, "[-] Error : cant find map file!", 31);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "[-] Error : invalid file name!", 30);
		return (0);
	}
	ml.map = mapper(fd);
	if (flood_fill(ml, 1, 1, '#') == 1)
		printf("\n\n\n\tmap is Goodn");
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
