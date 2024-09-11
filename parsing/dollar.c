/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:47 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/08 16:05:21 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_check(char **str, int *i, int sq, int dq)
{
	if ((*str)[(*i)] == '$' && ((*str)[(*i) + 1] == ' '
		|| (*str)[(*i) + 1] == '\t' || (*str)[(*i) + 1] == '\0'
		|| ((*str)[(*i) + 1] == 34 && dq % 2 != 0)
		|| ((*str)[(*i) + 1] == 39 && sq % 2 != 0)))
		(*i)++;
	else if ((*str)[(*i)] == '$' && (((*str)[(*i) + 1] == 34 && dq % 2 == 0)
		|| ((*str)[(*i) + 1] == 39 && sq % 2 == 0)))
		fill_space(*str, (*i), 1);
}

char	*dollar_line(char *val, char *s1, char *s2, t_mini *mini)
{
	char	*line;
	char	*value;
	char	*hold;

	if (!val)
		line = ft_strjoin(s1, s2);
	else
	{
		value = val_redirect(val, mini, 0, 0);
		free(val);
		hold = ft_strjoin(s1, value);
		line = ft_strjoin(hold, s2);
		free(hold);
		free(value);
	}
	return (line);
}

void	dollar_working(t_mini *mini, char **str, int *i)
{
	char	*hold;
	char	*val;
	char	*line;
	char	*s1;
	char	*s2;

	hold = dollar_business(*str, mini, &(*i));
	s1 = ft_substr(*str, 0, (*i));
	s2 = ft_substr(*str, (*i) + mini->redirect->len + 1, \
		ft_strlen(*str + ((*i) + mini->redirect->len)));
	val = env_contains(hold, mini);
	line = dollar_line(val, s1, s2, mini);
	free(*str);
	*str = ft_strdup(line);
	free(s1);
	free(s2);
	free(line);
	(*i) = 0;
}

char	*is_dollar_exist_and_valid(char *str, t_mini *mini, int sq, int dq)
{
	int	i;

	i = 0;
	while (str[i] && (quote_check(str[i], &sq, &dq), 1))
	{
		dollar_check(&str, &i, sq, dq);
		if (str[i] == '$' && (str[i + 1] == '0' || str[i + 1] == '?')
			&& sq % 2 == 0)
		{
			dollar_zero_question(&str, &i);
			continue ;
		}
		else if (str[i] == '$' && sq % 2 == 0)
		{
			dollar_working(mini, &str, &i);
			continue ;
		}
		if (str[i])
			i++;
	}
	return (str);
}

char	*val_redirect(char *s, t_mini *mini, int i, int j)
{
	int		redirect;
	char	*val;

	redirect = 0;
	mini->utils->sq = 0;
	mini->utils->dq = 0;
	while (s[i] && (quote_check(s[i], &mini->utils->sq, &mini->utils->dq), 1))
		count_redirect(s, mini, &redirect, &i);
	if (!redirect)
		return (ft_strdup(s));
	val = malloc((ft_strlen(s) + (redirect * 2) + 1));
	i = -1;
	while (s[++i] && (quote_check(s[i], &mini->utils->sq, &mini->utils->dq), 1))
	{
		if (s[i] == '<' && mini->utils->sq % 2 == 0)
			put_quotes(val, &j, s, &i);
		else if (s[i] == '>' && mini->utils->sq % 2 == 0)
			put_quotes(val, &j, s, &i);
		else if (s[i] == '|' && mini->utils->sq % 2 == 0)
			put_quotes(val, &j, s, &i);
		else
			val[j++] = s[i];
	}
	val[j] = '\0';
	return (val);
}
