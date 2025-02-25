/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:51:12 by diogribe          #+#    #+#             */
/*   Updated: 2025/02/24 18:51:11 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"

typedef struct	s_game {
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
}				t_game;

#endif