/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_prs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:41 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/08 15:00:43 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_check(char temp, int *squotes, int *dquotes)
{
	if (temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if (temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}

int	pp_counter(char *temp, int squotes, int dquotes, char c)
{
	int	i;
	int	d;

	d = 0;
	i = -1;
	while (temp[++i] && (quote_check(temp[i], &squotes, &dquotes), 1))
		if (temp[i] == c && (dquotes % 2 == 0 && squotes % 2 == 0))
			d++;
	d++;
	return (d);
}

void	sub(char *temp, char ***ret, char c, int j)
{
	int		i;
	int		d;
	int		squotes;
	int		dquotes;
	char	*tmp;

	i = -1;
	d = 0;
	squotes = 0;
	dquotes = 0;
	while (temp[++i] && (quote_check(temp[i], &squotes, &dquotes), 1))
	{
		if (temp[i] == c && (dquotes % 2 == 0 && squotes % 2 == 0))
		{
			tmp = ft_substr(temp, d, i - d);
			(*ret)[j] = ft_strtrim(tmp, " \t");
			free(tmp);
			j++;
			d = i + 1;
		}
	}
	tmp = ft_substr(temp, d, i - d);
	(*ret)[j++] = ft_strtrim(tmp, " \t");
	free(tmp);
	(*ret)[j] = NULL;
}

char	**mm_split(char *temp, char c)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (pp_counter(temp, 0, 0, c) + 1));
	if (!ret)
		return (NULL);
	sub(temp, &ret, c, 0);
	free(temp);
	temp = NULL;
	return (ret);
}
