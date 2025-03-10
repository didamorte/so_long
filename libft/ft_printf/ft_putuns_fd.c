/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:49:54 by diogribe          #+#    #+#             */
/*   Updated: 2025/02/03 20:18:12 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putuns_fd(unsigned int nb, int fd)
{
	int	count;

	count = 0;
	if (nb > 9)
	{
		count += ft_putuns_fd(nb / 10, fd);
		count += pf_ft_putchar_fd((nb % 10 + '0'), fd);
	}
	else
	{
		count += pf_ft_putchar_fd((nb + '0'), fd);
	}
	return (count);
}
