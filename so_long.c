/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:00 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/17 16:53:34 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	unknown_caracter(t_game game)
{
	int	x;
	int	y;
	int	len;
	int	j;

	y = 0;
	len = ft_strlen(game.map[y]);
	while (y < game.map_h)
	{
		x = 0;
		while (x < game.map_w)
		{
			if (game.map[y][x] != 'P' && game.map[y][x] != 'C'
				&& game.map[y][x] != 'E' && game.map[y][x] != '1'
				&& game.map[y][x] != '0')
				return (1);
			x++;
		}
		j = ft_strlen(game.map[y]);
		if (len != j && game.map[y][x] != '\0')
			return (1);
		y++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	if (load_map(argv[1], &game))
		return (ft_printf("Error\nImpossivel carregar mapa"),
			free_map(game.map, game.map_h));
	if (unknown_caracter(game))
		return (ft_printf("Error\nCaracteres errados no mapa\n"),
			free_map(game.map, game.map_h));
	find_player_position(&game);
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
