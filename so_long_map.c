/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:20:24 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/28 17:43:39 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(char *filename, t_game *game)
{
	int	fd;
	int	y;

	game->map = NULL;
	game->map_h = get_map_height(filename);
	if (game->map_h <= 0)
		return (1);
	game->map = malloc(sizeof(char *) * (game->map_h + 1));
	if (!game->map)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	y = -1;
	while (++y < game->map_h)
	{
		game->map[y] = get_next_line(fd);
		if (!game->map[y])
			break ;
		game->map_w = 0;
		while (game->map[y][game->map_w] && game->map[y][game->map_w] != '\n')
			game->map_w++;
	}
	get_next_line(-1);
	return (game->map[y] = NULL, close(fd));
}

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
				return (write(2, "Error\nInvalid characters\n", 25), 1);
			x++;
		}
		j = ft_strlen(game.map[y]);
		if ((len != j && game.map[y][x] != '\0') ||
			game.map_h < 3 || game.map_w < 3)
			return (write(2, "Error\nMap not rectangular\n", 26), 1);
		y++;
	}
	return (0);
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
		return (write(2, "Error\nInvalid path\n", 19));
	counters(&e_count, &p_count, &c_count, game);
	if (p_count > 1)
		return (write(2, "Error\nMore than 1 player\n", 25));
	if (e_count > 1)
		return (write(2, "Error\nMore than 1 exit\n", 23));
	if (e_count < 1)
		return (write(2, "Error\nNo exits found\n", 21));
	if (c_count < 1)
		return (write(2, "Error\nNo collectibles found\n", 28));
	if (game->valid_walls == 0)
		return (write(2, "Error\nMap is not closed\n", 24));
	game->collected = c_count;
	return (1);
}
