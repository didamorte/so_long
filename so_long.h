/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:51:12 by diogribe          #+#    #+#             */
/*   Updated: 2025/02/25 18:27:54 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "mlx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

// Size of each tile (square)
# define TILE_SIZE 50

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*floor;
	void	*house;
	void	*collect;
	void	*pl_r;
	void	*pl_l;
	int		img_w;
	int		img_h;
	int		pl_x;
	int		pl_y;
	int		map_w;
	int		map_h;
	char	**map;
	int		collected;
}				t_game;

/* Utils */

int		is_walkable(t_game game, int y, int x);
int		close_game(t_game *game);
void	free_map(t_game *game);
void	find_player_position(t_game *game);
int		get_map_height(char *filename);

/* Functions */

int		load_map(char *filename, t_game *game);
void	draw_map(t_game *game);
void	update_player_position(t_game *game, int old_x, int old_y, int direct);
int		key_hook(int keycode, t_game *game);
void	get_img(t_game *game);

#endif