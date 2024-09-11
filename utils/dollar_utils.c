/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:54:32 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/05 16:17:31 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_quotes(char *val, int *j, char *str, int *i)
{
	val[(*j)++] = 34;
	val[(*j)++] = str[(*i)];
	val[(*j)++] = 34;
}

void	count_redirect(char *str, t_mini *mini, int *redirect, int *i)
{
	if (str[(*i)] == '<' && mini->utils->sq % 2 == 0)
		(*redirect)++;
	if (str[(*i)] == '>' && mini->utils->sq % 2 == 0)
		(*redirect)++;
	if (str[(*i)] == '|' && mini->utils->sq % 2 == 0)
		(*redirect)++;
	(*i)++;
}

char	*env_contains(char *str, t_mini *mini)
{
	int		i;
	char	*value;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(str, "=");
	value = NULL;
	while (mini->env[i])
	{
		if (!ft_strncmp(tmp, mini->env[i], ft_strlen(tmp)))
			value = ft_substr(mini->env[i], ft_strlen(tmp), \
			(ft_strlen(mini->env[i]) - ft_strlen(tmp)));
		i++;
	}
	free(str);
	free(tmp);
	return (value);
}

void	take_name_for_dollar(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	mini->redirect->start += i;
	mini->redirect->len = 0;
	while (str[i])
	{
		if (ft_isdigit(str[0]))
		{
			mini->redirect->len += 1;
			break ;
		}
		if ((ft_isalnum(str[i]) == 0 && str[i] != '_'))
			break ;
		i++;
		mini->redirect->len += 1;
	}
}

char	*dollar_business(char *str, t_mini *mini, int *i)
{
	char	*hold;

	mini->redirect->start = (*i) + 1;
	take_name_for_dollar(str + ((*i) + 1), mini);
	hold = delete_quotes(\
	ft_substr(str, mini->redirect->start, mini->redirect->len), mini, 0, 0);
	return (hold);
}
