/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:44:58 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:45:00 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*put_the_exit(char **map, mlx_t *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				put_exit(mlx, j, i);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	put_walls(mlx_t *mlx, struct s_long mx)
{
	int				i;
	int				j;
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	i = 0;
	texture = mlx_load_png("./pngs/box.png");
	if (!texture)
		game_error(0);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		game_error(0);
	mlx_delete_texture(texture);
	while (mx.map[i])
	{
		j = 0;
		while (mx.map[i][j])
		{
			put_bg(mx.mlx, j, i);
			if (mx.map[i][j] == '1')
				mlx_image_to_window(mx.mlx, img, j * 65, i * 65);
			j++;
		}
		i++;
	}
}

void	put_collectibles(char **map, mlx_t *mlx)
{
	int				i;
	int				j;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	i = 0;
	texture = mlx_load_png("./pngs/fish.png");
	if (!texture)
		game_error(0);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		game_error(0);
	mlx_delete_texture(texture);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				mlx_image_to_window(mlx, img, j * 65, i * 65);
			j++;
		}
		i++;
	}
}

mlx_image_t	*put_player(char **map, mlx_t *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				return ((put_the_cat(mlx, j, i)));
			j++;
		}
		i++;
	}
	return (NULL);
}

mlx_image_t	*set_game(struct s_long *ml)
{
	put_walls(ml->mlx, *ml);
	put_collectibles(ml->map, ml->mlx);
	ml->imgg = put_player(ml->map, ml->mlx);
	put_the_exit(ml->map, ml->mlx);
	return (ml->imgg);
}
