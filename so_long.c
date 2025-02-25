/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:00 by diogribe          #+#    #+#             */
/*   Updated: 2025/02/25 16:38:38 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "so_long.h"

#define TILE_SIZE 50  // Size of each tile (square)

// Function to get the number of rows in the file
int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

// Function to load map from a `.ber` file
int	load_map(char *filename, t_game *game)
{
	int	fd;
	int	y;

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
	game->map[y] = NULL;
	close(fd);
	return (0);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->house,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collect,
					x * TILE_SIZE, y * TILE_SIZE);
			else
				mlx_put_image_to_window(game->mlx, game->win, game->floor,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	find_player_position(t_game *game)
{
	int	x;
	int	y;
	int	c;

	c = 0;
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == 'P')
			{
				game->pl_x = x;
				game->pl_y = y;
			}
			if (game->map[y][x] == 'C')
				c++;
			x++;
		}
		y++;
	}
	game->collected = c;
}

void	free_map(t_game *game)
{
	int	i;

	i = -1;
	if (!game->map)
		return ;
	while (++i < game->map_h)
		free(game->map[i]);
	free(game->map);
}

int	close_window(t_game *game)
{
	free_map(game);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	update_player_position(t_game *game, int old_x, int old_y, int direct)
{
	static int	moves;

	mlx_put_image_to_window(game->mlx, game->win, game->floor,
		old_x * TILE_SIZE, old_y * TILE_SIZE);
	moves++;
	ft_printf("Moves: %d\n", moves);
	if (direct == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->pl_r,
			game->pl_x * TILE_SIZE, game->pl_y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->pl_l,
			game->pl_x * TILE_SIZE, game->pl_y * TILE_SIZE);
	if (game->map[game->pl_y][game->pl_x] == 'C')
	{
		game->map[game->pl_y][game->pl_x] = '0';
		if (--game->collected > 0)
			ft_printf("Ovos restantes: %d\n", game->collected);
		else
			ft_printf("Apanhas-te os ovos todos!\nAgora volta pra casa.\n");
	}
	if (game->map[game->pl_y][game->pl_x] == 'E' && game->collected == 0)
	{
		ft_printf("Parabéns! Voltas-te para casa em segurança!\n");
		close_window(game);
	}
}

int	is_walkable(t_game game, int y, int x)
{
	if (game.map[y][x] == '1')
		return (0);
	if (game.map[y][x] == 'E' && game.collected != 0)
	{
		ft_printf("Volta! Ainda faltam %d ovos\n", game.collected);
		return (0);
	}
	return (1);
}

// Função para lidar com teclas pressionadas
int	key_hook(int keycode, t_game *game)
{
	int			old_x;
	int			old_y;
	static int	direct;

	old_x = game->pl_x;
	old_y = game->pl_y;
	if (keycode == 65307 || keycode == 113)
		close_window(game);
	else if (keycode == 97 && is_walkable(*game, game->pl_y, game->pl_x - 1))
	{
		game->pl_x -= 1;
		direct = 1;
	}
	else if (keycode == 100 && is_walkable(*game, game->pl_y, game->pl_x + 1))
	{
		game->pl_x += 1;
		direct = 0;
	}
	else if (keycode == 119 && is_walkable(*game, game->pl_y - 1, game->pl_x))
		game->pl_y -= 1;
	else if (keycode == 115 && is_walkable(*game, game->pl_y + 1, game->pl_x))
		game->pl_y += 1;
	if (old_x != game->pl_x || old_y != game->pl_y)
		update_player_position(game, old_x, old_y, direct);
	return (0);
}

void	get_img(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map_w * TILE_SIZE,
			game->map_h * TILE_SIZE, "so_long");
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/Wall.xpm",
			&game->img_w, &game->img_h);
	game->floor = mlx_xpm_file_to_image(game->mlx, "textures/Floor.xpm",
			&game->img_w, &game->img_h);
	game->house = mlx_xpm_file_to_image(game->mlx, "textures/House.xpm",
			&game->img_w, &game->img_h);
	game->pl_r = mlx_xpm_file_to_image(game->mlx, "textures/Player_right.xpm",
			&game->img_w, &game->img_h);
	game->pl_l = mlx_xpm_file_to_image(game->mlx, "textures/Player_left.xpm",
			&game->img_w, &game->img_h);
	game->collect = mlx_xpm_file_to_image(game->mlx, "textures/Egg.xpm",
			&game->img_w, &game->img_h);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	game.mlx = mlx_init();
	if (load_map(argv[1], &game))
		return (1);
	get_img(&game);
	if (!game.wall || !game.floor || !game.house || !game.pl_r
		|| !game.pl_l || !game.collect)
		return (1);
	find_player_position(&game);
	draw_map(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.pl_r,
		game.pl_x * TILE_SIZE, game.pl_y * TILE_SIZE);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	free_map(&game);
	return (0);
}
