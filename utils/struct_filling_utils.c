/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:02:36 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/08 16:03:50 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	struct_business(t_mini *mini)
{
	mini->redirect = malloc(sizeof(t_redirect));
	mini->redirect->output = 0;
	mini->redirect->input = 0;
	mini->redirect->heredoc = 0;
	mini->redirect->append = 0;
	mini->utils = malloc(sizeof(t_utils));
	mini->utils->d = 0;
	mini->utils->k = 0;
	mini->utils->z = 0;
	mini->utils->l = 0;
	mini->append = NULL;
	mini->output = NULL;
	mini->input = NULL;
	mini->heredoc = NULL;
	mini->cmd = NULL;
	mini->flag_arg = NULL;
	mini->status = NONE;
}

void	take_name(char *args, t_mini *mini)
{
	int	i;

	i = 0;
	mini->redirect->len = 0;
	mini->utils->j = 0;
	mini->utils->dq = 0;
	mini->utils->sq = 0;
	while (args[i] && (args[i] == ' ' || args[i] == '\t'))
	{
		i++;
		mini->utils->j++;
	}
	mini->redirect->start += i;
	while (args[i]
		&& (quote_check(args[i], &mini->utils->sq, &mini->utils->dq), 1))
	{
		if ((mini->utils->dq % 2 == 0 && mini->utils->sq % 2 == 0)
			&& ((args[i] == ' ' || args[i] == '\t')
				|| (args[i] == '<' || args[i] == '>' || args[i] == '|'
					|| (args[i] == '$' && ft_isalnum(args[i + 1])))))
			break ;
		i++;
		mini->utils->j++;
		mini->redirect->len += 1;
	}
}

void	imp(t_mini *mini, int *i, char *str, int n)
{
	if (n == 1)
	{
		mini->redirect->start = (*i) + 1;
		take_name(str + ((*i) + 1), mini);
		mini->input[mini->utils->z++] = delete_quotes(ft_substr(str, \
			mini->redirect->start, mini->redirect->len), mini, 0, 0);
		fill_space(str, (*i), mini->utils->j + 1);
	}
	if (n == 2)
	{
		mini->redirect->start = (*i) + 1;
		take_name(str + ((*i) + 1), mini);
		mini->output[mini->utils->d++] = delete_quotes(ft_substr(str, \
			mini->redirect->start, mini->redirect->len), mini, 0, 0);
		fill_space(str, (*i), mini->utils->j + 1);
	}
}

void	imp2(t_mini *mini, int *i, char *str, int n)
{
	if (n == 3)
	{
		mini->redirect->start = (*i) + 2;
		take_name(str + ((*i) + 2), mini);
		mini->heredoc[mini->utils->k++] = delete_quotes(ft_substr(str, \
			mini->redirect->start, mini->redirect->len), mini, 0, 0);
		fill_space(str, (*i), mini->utils->j + 2);
		i++;
	}
	if (n == 4)
	{
		mini->redirect->start = (*i) + 2;
		take_name(str + ((*i) + 2), mini);
		mini->append[mini->utils->l++] = delete_quotes(ft_substr(str, \
			mini->redirect->start, mini->redirect->len), mini, 0, 0);
		fill_space(str, (*i), mini->utils->j + 2);
		i++;
	}
}

void	allocate(t_mini *mini)
{
	if (mini->redirect->input != 0)
	{
		mini->input = malloc(sizeof(char *) * (mini->redirect->input + 1));
		mini->input[mini->redirect->input] = NULL;
		if (!mini->input)
			perror ("Malloc!\n");
	}
	if (mini->redirect->output != 0)
	{
		mini->output = malloc(sizeof(char *) * (mini->redirect->output + 1));
		mini->output[mini->redirect->output] = NULL;
		if (!mini->output)
			perror ("Malloc!\n");
	}
	allocate_continue(mini);
}
