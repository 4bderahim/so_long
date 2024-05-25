/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mlxs_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:44:04 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:44:06 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_error_msg(const char *error_msg)
{
	int	i;

	i = 0;
	write(2, "Error\n[-] ", 10);
	while (error_msg[i])
	{
		write(2, &error_msg[i], 1);
		i++;
	}
}

void	game_error(int err_flag)
{
	const char	*msg;

	msg = mlx_strerror(mlx_errno);
	if (err_flag)
		msg = "Invalid map!";
	put_error_msg(msg);
	exit(EXIT_FAILURE);
}

void	put_exit(mlx_t *mlx, int j, int i)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png("./pngs/exit_door.png");
	if (!texture)
		game_error(0);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		game_error(0);
	mlx_delete_texture(texture);
	mlx_image_to_window(mlx, img, j * 65, i * 65);
}

mlx_image_t	*put_the_cat(mlx_t *mlx, int j, int i)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png("./pngs/caat.png");
	if (!texture)
		game_error(0);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		game_error(0);
	mlx_image_to_window(mlx, img, j * 65, i * 65);
	mlx_delete_texture(texture);
	return (img);
}
