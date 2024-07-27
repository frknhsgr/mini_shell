/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:28:14 by fhosgor           #+#    #+#             */
/*   Updated: 2023/10/13 19:00:28 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*dest;
	char	*sorc;
	size_t	i;

	i = 0;
	dest = dst;
	sorc = (char *)src;
	if (dstsize > 0)
	{
		while (sorc[i] && i < dstsize - 1)
		{
			dest[i] = sorc[i];
			i++;
		}
		dest[i] = '\0';
	}
	i = ft_strlen(src);
	return (i);
}
