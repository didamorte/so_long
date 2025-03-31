/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:00 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/28 17:37:10 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || !is_ber_file(av[1]))
		return (1);
	if (load_map(av[1], &game))
		return (write(2, "Error\nCan't load map\n", 21),
			free_map(game.map, game.map_h));
	if (unknown_caracter(game))
		return (free_map(game.map, game.map_h));
	if (find_player_position(&game))
		return (write(2, "Error\nNo players found\n", 23),
			free_map(game.map, game.map_h));
	if (map_valid(&game) != 1)
		return (free_map(game.map, game.map_h));
	game.mlx = mlx_init();
	get_img(&game);
	if (!game.wall || !game.floor || !game.house || !game.pl_r
		|| !game.pl_l || !game.collect)
		return (close_game(&game), 1);
	draw_map(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.pl_r,
		game.pl_x * TILE_SIZE, game.pl_y * TILE_SIZE);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
}
