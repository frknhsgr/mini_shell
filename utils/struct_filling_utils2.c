/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:06:31 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/08 19:00:51 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	to_do_newline1(t_mini *mini, int *i, char *str, char **tmp)
{
	int	a;

	mini->redirect->start = (*i) + 1;
	take_name(str + (*i) + 1, mini);
	*tmp = ft_substr(str, mini->redirect->start, mini->redirect->len);
	a = error_message_newline((*tmp), mini);
	if (*tmp && *tmp[0])
		free(*tmp);
	return (a);
}

int	to_do_newline2(t_mini *mini, int *i, char *str, char **tmp)
{
	int	a;

	mini->redirect->start = (*i) + 2;
	take_name(str + (*i) + 2, mini);
	*tmp = ft_substr(str, mini->redirect->start, mini->redirect->len);
	a = error_message_newline((*tmp), mini);
	if (*tmp && *tmp[0])
		free(*tmp);
	return (a);
}

int	is_valid_name(char *str, t_mini *mini, int sq, int dq)
{
	int		i;
	char	*tmp;

	i = 0;
	struct_business(mini);
	while (str[i] && (quote_check(str[i], &sq, &dq), 1))
	{
		if ((str[i] == '<' && str[i + 1] != '<'
				&& (dq % 2 == 0) && (sq % 2 == 0))
			|| (str[i] == '>' && str[i + 1] != '>'
				&& (dq % 2 == 0) && (sq % 2 == 0)))
		{
			if (!to_do_newline1(mini, &i, str, &tmp))
				return (0);
		}
		else if ((str[i] == '<' && str[i + 1] == '<'
				&& (dq % 2 == 0) && (sq % 2 == 0))
			|| (str[i] == '>' && str[i + 1] == '>'
				&& (dq % 2 == 0) && (sq % 2 == 0)))
			if (!to_do_newline2(mini, &i, str, &tmp))
				return (0);
		i++;
	}
	return (1);
}

void	fill_space(char *str, int start, int len)
{
	int	s;

	s = 0;
	while (len > s)
	{
		str[start] = ' ';
		start++;
		s++;
	}
}

void	pipe_while(char *str, int *i, int *control, int *quote)
{
	int	dq;
	int	sq;

	sq = 0;
	dq = 0;
	while (str[(*i)] && str[(*i)] != '|' && (quote_check(str[*i], &sq, &dq), 1))
	{
		if (str[(*i)] == '<' || str[(*i)] == '>')
			(*control) = 0;
		else if (str[(*i)] != ' ' && str[(*i)] != '\t' )
			(*control) = 1;
		(*i)++;
	}
	if (sq % 2 != 0 || dq % 2 != 0)
		*quote = 1;
}
