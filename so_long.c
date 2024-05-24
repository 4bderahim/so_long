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

int	main(int argc, char **argv)
{
	struct s_long	ml;

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
	free_map(ml);
	ml.map = get_map_from_file(argv[1]);
	check_map(ml.map);
	ml.mlx = mlx_init(get_height_width(ml.map, 0) * 65, get_height_width(ml.map, 1)
			* 65, "so long", false);
	if (!ml.mlx)
		game_error(0);
	ml.imgg = set_game(&ml);
	mlx_key_hook(ml.mlx, ft_hook, &ml);
	mlx_loop(ml.mlx);
	mlx_terminate(ml.mlx);
	mlx_delete_image(ml.mlx, ml.imgg);
	free_map(ml);
	atexit(check_leaks);
	//system("leaks -q Game");	
	return (0);
}
