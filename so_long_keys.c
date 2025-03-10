/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:24:22 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/10 19:02:13 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_up(int keycode)
{
	if (keycode == 115 || keycode == 65364)
		return (1);
	return (0);
}

int	key_down(int keycode)
{
	if (keycode == 119 || keycode == 65362)
		return (1);
	return (0);
}

int	key_left(int keycode)
{
	if (keycode == 97 || keycode == 65361)
		return (1);
	return (0);
}

int	key_right(int keycode)
{
	if (keycode == 100 || keycode == 65363)
		return (1);
	return (0);
}
