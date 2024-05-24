/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_join_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:54 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:43:56 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_map_hpaths(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && (s[i + 1] == '\0' || s[i + 1] == '\n'))
			count++;
		i++;
	}
	return (count);
}

void	join_to_map(char **sp, char *s, int ii, int index)
{
	int	i;

	i = 0;
	if (ii != 0)
		ii++;
	s = s + ii;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	sp[index] = (char *)malloc(i + 1);
	if (!sp[index])
		return ;
	sp[index][i] = 0;
	i = 0;
	while (s[i] != 0 && s[i] != '\n')
	{
		sp[index][i] = s[i];
		i++;
	}
}

char	**mapper(int fd)
{
	char	*map_full_road;
	char	**spilited_map;
	int		i;
	int		index;

	index = 0;
	i = 0;
	map_full_road = map_reader(fd);
	if (!map_full_road)
		game_error(1);
	spilited_map = (char **)malloc(sizeof(char *)
			* (count_map_hpaths(map_full_road) + 1));
	if (!spilited_map)
		game_error(1);
	spilited_map[count_map_hpaths(map_full_road)] = NULL;
	while (map_full_road[i])
	{
		if (map_full_road[i] == '\n' || i == 0)
		{
			join_to_map(spilited_map, map_full_road, i, index);
			index++;
		}
		i++;
	}
	return (free(map_full_road), spilited_map);
}
