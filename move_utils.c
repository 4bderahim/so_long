/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:45:10 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:45:11 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_collect(char **map)
{
	int	i;
	int	j;

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

void	next_step(struct s_long *l, int direction)
{
	struct s_long	ll;

	ll = *l;
	if (direction == 1)
		ll.imgg->instances[0].y = ll.cu_y - 65;
	if (direction == 3)
		ll.imgg->instances[0].y = ll.cu_y + 65;
	if (direction == 2)
		ll.imgg->instances[0].x = ll.cu_x + 65;
	if (direction == 4)
		ll.imgg->instances[0].x = ll.cu_x - 65;
	if (ll.map[ll.cu_y / 65][ll.cu_x / 65] != 'E')
		ll.map[ll.cu_y / 65][ll.cu_x / 65] = '0';
	if (ll.map[ll.cu_y / 65][ll.cu_x / 65] == 'E')
		put_exit(ll.mlx, ll.cu_x / 65, ll.cu_y / 65);
	else
		put_bg(ll.mlx, ll.cu_x / 65, ll.cu_y / 65);
	*l = ll;
}

int32_t	get_x_y(mlx_image_t *img_ins, int direction, char order)
{
	int32_t	x;
	int32_t	y;

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

int	move_the_player(struct s_long *mx, int direction)
{
	struct s_long	mlx;
	int32_t			y;
	int32_t			x;

	mlx = *mx;
	mlx.cu_x = mlx.imgg->instances[0].x;
	mlx.cu_y = mlx.imgg->instances[0].y;
	y = get_x_y(mlx.imgg, direction, 'y');
	x = get_x_y(mlx.imgg, direction, 'x');
	if (mlx.map[y][x] == '1')
		return (0);
	if (mlx.map[y][x] == 'C')
		put_bg(mlx.mlx, x, y);
	if (mlx.map[y][x] == 'E')
	{
		if (!check_collect(mlx.map))
			mlx_close_window(mlx.mlx);
		put_exit(mlx.mlx, x, y);
	}
	else
		mlx.map[y][x] = 'P';
	next_step(&mlx, direction);
	mlx.imgg = put_the_cat(mlx.mlx, x, y);
	*mx = mlx;
	return (1);
}
