/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:08:36 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/11 18:51:12 by diogribe         ###   ########.fr       */
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
void	find_player_position(t_game *game)
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
			{
				game->pl_x = x;
				game->pl_y = y;
			}
			x++;
		}
		y++;
	}
}

// Free map
int	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return (-1);
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
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->floor);
	mlx_destroy_image(game->mlx, game->house);
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->pl_l);
	mlx_destroy_image(game->mlx, game->pl_r);
	mlx_destroy_image(game->mlx, game->collect);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
	return (0);
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
