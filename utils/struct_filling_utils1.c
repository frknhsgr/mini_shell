/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:04:47 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 16:47:17 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocate_continue(t_mini *mini)
{
	if (mini->redirect->heredoc != 0)
	{
		mini->heredoc = malloc(sizeof(char *) * (mini->redirect->heredoc + 1));
		mini->heredoc[mini->redirect->heredoc] = NULL;
		if (!mini->heredoc)
			perror ("Malloc!\n");
	}
	if (mini->redirect->append != 0)
	{
		mini->append = malloc(sizeof(char *) * (mini->redirect->append + 1));
		mini->append[mini->redirect->append] = NULL;
		if (!mini->append)
			perror ("Malloc!\n");
	}
}

char	*delete_quotes(char *str, t_mini *mini, int i, int j)
{
	char	*hold;

	mini->utils->dq = 0;
	mini->utils->sq = 0;
	while (str[i]
		&& (quote_check(str[i], &mini->utils->sq, &mini->utils->dq), 1))
		i++;
	j = ft_strlen(str) - (mini->utils->sq + mini->utils->dq);
	hold = malloc(sizeof(char) * (j + 1));
	if (!hold)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i]
		&& (quote_check(str[i], &mini->utils->sq, &mini->utils->dq), 1))
	{
		if ((str[i] == 39 && mini->utils->dq % 2 == 0)
			|| (str[i] == 34 && mini->utils->sq % 2 == 0))
			i++;
		else
			hold[j++] = str[i++];
	}
	hold[j] = '\0';
	free(str);
	return (hold);
}

int	is_quotes_closed(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] && (quote_check(str[i], &sq, &dq), 1))
		i++;
	if (sq % 2 != 0 || dq % 2 != 0)
	{
		printf("dquotes!\n");
		g_global_exit = 258;
		return (0);
	}
	return (1);
}

int	error_message_newline(char *tmp, t_mini *mini)
{
	if (tmp[0] == '\0')
	{
		free(mini->redirect);
		mini->redirect = NULL;
		free(mini->utils);
		mini->utils = NULL;
		free(tmp);
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
		return (0);
	}
	return (1);
}

void	take_cmd(char *str, t_mini *mini)
{
	char	*temp;

	temp = ft_strtrim(str, " \t");
	if (!temp[0])
	{
		mini->cmd = NULL;
		free (temp);
		return ;
	}
	mini->redirect->start = 0;
	take_name(str, mini);
	mini->cmd = delete_quotes(ft_substr(str, \
		mini->redirect->start, mini->redirect->len), mini, 0, 0);
	fill_space(str, mini->redirect->start, mini->redirect->len);
	free(temp);
}
