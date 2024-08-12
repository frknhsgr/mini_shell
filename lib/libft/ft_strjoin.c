/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:47:22 by fhosgor           #+#    #+#             */
/*   Updated: 2023/10/16 17:51:03 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	i;
	int		j;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	a = malloc(i + 1);
	if (!a)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		a[j] = ((unsigned char *)s1)[j];
		j++;
	}
	k = 0;
	while (s2[k])
		a[j++] = ((unsigned char *)s2)[k++];
	a[j] = '\0';
	return (a);
}
