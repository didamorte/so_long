/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:05:42 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:09:08 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y, t_game game)
{
	if (x < 0 || y < 0 || x >= game.map_w || y >= game.map_h)
		return ;
	if (map[y][x] == 'E')
		map[y][x] = 'I';
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'I')
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

int	is_ber_file(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".ber", 4) != 0)
	{
		write(2, "Error\nInvalid file, use .ber\n", 29);
		return (0);
	}
	return (1);
}
