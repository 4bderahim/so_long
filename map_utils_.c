/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:45:10 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:45:11 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(struct s_long *st, int y, int x, char c)
{
	int	height;
	int	width;

	height = get_height_width(st->map, 1);
	width = get_height_width(st->map, 0);
	if (st->map[y][x] == 'C')
		st->coins_num--;
	if (st->map[y][x] == 'E')
		st->exit_found++;
	if (y == 0 || y >= height || x >= width || x == 0 || st->map[y][x] == c
		|| st->map[y][x] == '1')
	{
		return ;
	}
	st->map[y][x] = '#';
	flood_fill(st, y + 1, x, '#');
	flood_fill(st, y - 1, x, '#');
	flood_fill(st, y, x + 1, '#');
	flood_fill(st, y, x - 1, '#');
}

int	coins_len(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
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

int	get_player_position(char **map, char c)
{
	int	x;
	int	y;

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

char	**get_map_from_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n[-] invalid file name!", 28);
		exit(1);
	}
	return (mapper(fd));
}

struct s_long	set_struct(char *file_name)
{
	struct s_long	sl;

	sl.map = get_map_from_file(file_name);
	sl.coins_num = coins_len(sl.map);
	if (!sl.coins_num)
		{

			write(2, "Error\n[-] cant find map file!", 29);
			exit(1);
		}
	sl.exit_found = 0;
	sl.moves = 0;
	return (sl);
}
