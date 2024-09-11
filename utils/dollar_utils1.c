/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:57:52 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/07 18:17:26 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_zero_question_free(char **str, char *hold, char *s1, char *s2)
{
	char	*line;

	line = ft_strjoin(hold, s2);
	free(hold);
	free(*str);
	*str = ft_strdup(line);
	free(s1);
	free(s2);
	free(line);
}

void	dollar_zero_question(char	**str, int *i)
{
	char	*hold;
	char	*val;
	char	*s1;
	char	*s2;

	s1 = ft_substr(*str, 0, (*i));
	s2 = ft_substr(*str, (*i) + 2, ft_strlen((*str) + (*i) + 2));
	if ((*str)[(*i) + 1] == '0')
		hold = ft_strjoin(s1, "./minishell");
	else
	{
		val = ft_itoa(g_global_exit);
		hold = ft_strjoin(s1, val);
		free(val);
	}
	dollar_zero_question_free(str, hold, s1, s2);
	(*i) = 0;
}
