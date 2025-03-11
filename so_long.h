/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:51:12 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/11 18:33:03 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

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
	int		validWalls;
}				t_game;

/* Utils */

int		is_walkable(t_game game, int y, int x);
int		close_game(t_game *game);
int		free_map(char **map, int height);
void	find_player_position(t_game *game);
int		get_map_height(char *filename);

/* Functions */

int		load_map(char *filename, t_game *game);
void	draw_map(t_game *game);
void	update_player_position(t_game *game, int old_x, int old_y, int direct);
int		key_hook(int keycode, t_game *game);
void	get_img(t_game *game);

/* Keys */

int		key_up(int keycode);
int		key_down(int keycode);
int		key_left(int keycode);
int		key_right(int keycode);

/* Map */

int		map_valid(t_game *game);

#endif