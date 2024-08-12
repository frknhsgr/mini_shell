/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:27:55 by fhosgor           #+#    #+#             */
/*   Updated: 2023/10/17 17:15:29 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*sorc;
	char		*dest;
	size_t		i;

	sorc = src;
	dest = dst;
	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	else if (dst < src)
		ft_memcpy(dest, src, len);
	else if (src < dst)
	{
		while (len > 0)
		{
			len--;
			dest[len] = sorc[len];
		}
	}
	return (dst);
}
