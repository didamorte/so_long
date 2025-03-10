/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:57:51 by diogribe          #+#    #+#             */
/*   Updated: 2024/10/25 13:10:50 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		i;

	i = ft_strlen(s) + 1;
	d = malloc(i);
	if (d == NULL)
		return (NULL);
	ft_memcpy(d, s, i);
	return (d);
}
/* int main()
{
	char	*str = "ola mundo";
	char	*dup = ft_strdup(str);
	printf("%s", dup);
	free(dup);
} */