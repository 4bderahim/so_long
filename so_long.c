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

// #define HEIGHT 600
// #define WIDTH 900

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

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	struct s_long	mx;
	int 			mv;

	(void)keydata;
	mv = 0;
	mx = *(struct s_long *)param;
	if (mlx_is_key_down(mx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mx.mlx);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_UP))
		mv = move_the_player(&mx, 1);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_RIGHT))
		mv = move_the_player(&mx, 2);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_LEFT))
		mv = move_the_player(&mx, 4);
	else if (mlx_is_key_down(mx.mlx, MLX_KEY_DOWN))
		mv = move_the_player(&mx, 3);
	if (!mv)
		return ;
	mx.moves++;
	write(1, "\n", 1);
	putnbr(mx.moves);
	*((struct s_long *)param) = mx;
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
void d()
{
	system("leaks -q Game");
}
int	main(int argc, char **argv)
{
	struct s_long	ml;

	if (argc != 2)
	{
		write(2, "Error\n[-] cant find map file!", 29);
		return (1);
	}
	atexit(d);
	ml = set_struct(argv[1]);
	check_map(ml.map);
	flood_fill(&ml, get_player_position(ml.map, 'y'),
		get_player_position(ml.map, 'x'), '#');
	if (ml.coins_num || !ml.exit_found)
		game_error(1);
	free_map(ml);
	ml.map = get_map_from_file(argv[1]);
	ml.mlx = mlx_init(get_height_width(ml.map, 0) * 65, get_height_width(ml.map,
				1) * 65, "so long", false);
	if (!ml.mlx)
		game_error(0);
	ml.imgg = set_game(&ml);
	mlx_key_hook(ml.mlx, ft_hook, &ml);
	mlx_loop(ml.mlx);
	mlx_terminate(ml.mlx);
	mlx_delete_image(ml.mlx, ml.imgg);
	return (free_map(ml), 0);
}
