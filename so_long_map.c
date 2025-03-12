/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:20:24 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/12 17:53:24 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y, t_game game)
{
	if (x < 0 || y < 0 || x >= game.map_w || y >= game.map_h)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

char	**copy_map(char **map, int width, int height)
{
	int		y;
	char	**new_map;

	y = 0;
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (y < height)
	{
		new_map[y] = malloc(sizeof(char) * (width + 1));
		if (!new_map[y])
		{
			free_map(new_map, y);
			return (NULL);
		}
		ft_strlcpy(new_map[y], map[y], width + 1);
		y++;
	}
	new_map[height] = NULL;
	return (new_map);
}

int	is_valid_path(t_game game)
{
	int		y;
	int		x;
	char	**map_copy;

	map_copy = copy_map(game.map, game.map_w, game.map_h);
	if (!map_copy)
		return (0);
	flood_fill(map_copy, game.pl_x, game.pl_y, game);
	y = 0;
	while (y < game.map_h)
	{
		x = 0;
		while (x < game.map_w)
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				free_map(map_copy, game.map_h);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_map(map_copy, game.map_h);
	return (1);
}

void	counters(int *e_count, int *p_count, int *c_count, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == 'P')
				*p_count += 1;
			else if (game->map[y][x] == 'E')
				*e_count += 1;
			else if (game->map[y][x] == 'C')
				*c_count += 1;
			if (game->map[0][x] != '1' || game->map[y][0] != '1'
				|| game->map[game->map_h - 1][x] != '1'
				|| game->map[y][game->map_w - 1] != '1')
				game->valid_walls = 0;
			x++;
		}
		y++;
	}
}

int	map_valid(t_game *game)
{
	int	e_count;
	int	p_count;
	int	c_count;

	e_count = 0;
	p_count = 0;
	c_count = 0;
	game->valid_walls = 1;
	if (!is_valid_path(*game))
		return (write(2, "Error\nCaminho invalido\n", 24));
	counters(&e_count, &p_count, &c_count, game);
	if (p_count != 1)
		return (write(2, "Error\nPlayers a mais\n", 22));
	if (e_count != 1)
		return (write(2, "Error\nSaidas a mais\n", 21));
	if (c_count < 1)
		return (write(2, "Error\nNenhum colecionavel\n", 27));
	if (game->valid_walls == 0)
		return (write(2, "Error\nMapa nao rodeado\n", 24));
	game->collected = c_count;
	return (1);
}
