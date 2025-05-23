/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:08:36 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 15:08:55 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Get the number of rows in the file
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
	if (!line || line[0] != '1')
		return (free(line), close(fd), get_next_line(-1), -1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	return (height);
}

// Find player
int	find_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->pl_x = -1;
	game->pl_y = -1;
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
			x++;
		}
		y++;
	}
	if (game->pl_x == -1 && game->pl_y == -1)
		return (1);
	else
		return (0);
}

// Free map
int	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return (1);
	i = -1;
	while (++i < height)
		free(map[i]);
	free(map);
	return (1);
}

// Free map, imgs and display
int	close_game(t_game *game)
{
	free_map(game->map, game->map_h);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->house)
		mlx_destroy_image(game->mlx, game->house);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->pl_l)
		mlx_destroy_image(game->mlx, game->pl_l);
	if (game->pl_r)
		mlx_destroy_image(game->mlx, game->pl_r);
	if (game->collect)
		mlx_destroy_image(game->mlx, game->collect);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit (0);
	return (0);
}

int	is_walkable(t_game game, int y, int x)
{
	if (game.map[y][x] == '1')
		return (0);
	if (game.map[y][x] == 'E' && game.collected != 0)
	{
		ft_printf("Go back! There are eggs still missing\n",
			game.collected);
		return (0);
	}
	return (1);
}
