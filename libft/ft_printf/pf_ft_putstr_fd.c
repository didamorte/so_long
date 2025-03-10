/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_putstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:45:27 by diogribe          #+#    #+#             */
/*   Updated: 2025/02/03 20:18:12 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		s = "(null)";
	while (s[i])
	{
		pf_ft_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}
