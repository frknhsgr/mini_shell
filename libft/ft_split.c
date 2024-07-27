/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:35:14 by fhosgor           #+#    #+#             */
/*   Updated: 2023/10/16 16:25:57 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_words(char const *s, int i, int wordl)
{
	char	*dst;
	int		j;

	j = 0;
	dst = malloc(wordl + 1);
	if (!dst)
		return (NULL);
	while (wordl > 0)
	{
		dst[j] = s[i - wordl];
		j++;
		wordl--;
	}
	dst[j] = 0;
	return (dst);
}

static char	**ft_split_words(char **res, char const *s, char c, int wordc)
{
	int	i;
	int	j;
	int	wordl;

	i = 0;
	j = 0;
	wordl = 0;
	while (s[i] && j < wordc)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			wordl++;
		}
		res[j] = ft_words(s, i, wordl);
		wordl = 0;
		j++;
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		i;

	if (s == 0)
		return (NULL);
	i = ft_countwords(s, c);
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	dst = ft_split_words(dst, s, c, i);
	return (dst);
}
