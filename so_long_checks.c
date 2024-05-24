/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:45:52 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:45:53 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	borders_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (i == 0 || map[i + 1] == NULL)
		{
			while (map[i][j])
			{
				if (map[i][j] != '1')
					return (0);
				j++;
			}
		}
		else
		{
			if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

int	a_map_brick(char c)
{
	int		i;
	int		p_found;
	char	*s;

	p_found = 0;
	i = 0;
	s = "01CPE";
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_exit(char **map)
{
	int	i;
	int	j;
	int	e_found;

	e_found = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'E' && e_found))
				return (0);
			else if (map[i][j] == 'E')
				e_found = 1;
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_bricks(char **map)
{
	int	i;
	int	j;
	int	p_found;

	p_found = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		if (ft_strlen(map[i]) != ft_strlen(map[0]))
			return (0);
		while (map[i][j])
		{
			if ((map[i][j] == 'P' && p_found) || !check_exit(map))
				return (0);
			else if (map[i][j] == 'P')
				p_found = 1;
			if (!a_map_brick(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


int	check_map(char **map)
{
	int	i;

	i = 0;
	if (!check_map_bricks(map) || !borders_check(map))
	{
		game_error(1);
		exit(1);
	}
	return (0);
}
