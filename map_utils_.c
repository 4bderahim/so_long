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

void	flood_fill(char **map, int y, int x, char c, int *coins_len,
		int *exit_found)
{
	int	height;
	int	width;

	height = get_height_width(map, 1);
	width = get_height_width(map, 0);
	if (map[y][x] == 'C')
		(*coins_len)--;
	if (map[y][x] == 'E')
		(*exit_found)++;
	if (y == 0 || y >= height || x >= width || x == 0 || map[y][x] == c
		|| map[y][x] == '1')
	{
		
		return ;
	}
	map[y][x] = '#';
	flood_fill(map, y + 1, x, '#', coins_len, exit_found);
	flood_fill(map, y - 1, x, '#', coins_len, exit_found);
	flood_fill(map, y, x + 1, '#', coins_len, exit_found);
	flood_fill(map, y, x - 1, '#', coins_len, exit_found);
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
		write(2, "[-] Error : invalid file name!", 30);
		exit(1);
	}
	return (mapper(fd));
}
struct s_long	set_struct(char *file_name)
{
	struct s_long sl;
	sl.map = get_map_from_file(file_name);
	sl.coins_num = coins_len(sl.map);
	sl.exit_found = 0;
	return (sl);
}