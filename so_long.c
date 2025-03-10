/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:00 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/10 17:54:32 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	game.mlx = mlx_init();
	if (load_map(argv[1], &game))
		return (1);
	find_player_position(&game);
	if (map_valid(&game) != 1)
		return (1);
	get_img(&game);
	if (!game.wall || !game.floor || !game.house || !game.pl_r
		|| !game.pl_l || !game.collect)
		return (1);
	draw_map(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.pl_r,
		game.pl_x * TILE_SIZE, game.pl_y * TILE_SIZE);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	close_game(&game);
	return (0);
}
