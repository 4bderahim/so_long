/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:45:24 by ael-krid          #+#    #+#             */
/*   Updated: 2024/05/23 11:45:25 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "MLX42.h"
#include <MLX42/MLX42.h>
#include <errno.h>
#include <string.h>
#ifndef SO_LONG
# define SO_LONG

struct			s_long
{
	mlx_t		*mlx;
	char		**map;
	mlx_image_t	*imgg;
	int32_t		cu_y;
	int32_t		cu_x;
	int			moves;
	int			coins_num;
	int			exit_found;
	int 		p_position_x;
	int 		p_position_y;
};
int				ft_strlen(char const *s);
int				check_map(char **map);
void			move_the_player(struct s_long *mx, int direction);
mlx_image_t		*set_game(struct s_long *ml);
mlx_image_t		*put_the_cat(mlx_t *mlx, int j, int i);
void			put_bg(mlx_t *mlx, int j, int i);
void			put_exit(mlx_t *mlx, int j, int i);
mlx_image_t		*put_player(char **map, mlx_t *mlx);
void			put_walls(mlx_t *mlx, struct s_long mx);
void			game_error(int err_flag);
char			**mapper(int fd);
char			*map_reader(int fd);
void			flood_fill(struct s_long *st, int y, int x, char c);
int				get_player_position(char **map, char c);
char			**get_map_from_file(char *file_name);
struct s_long	set_struct(char *file_name);
int				get_height_width(char **map, int height_or_width_command);
#endif
