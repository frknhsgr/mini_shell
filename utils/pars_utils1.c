/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:15:30 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/23 14:15:31 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	status_regulator_pipe(t_mini *mini)
{
	if (mini->status == HEREDOC)
		mini->status = PIPEHEREDOC;
	else if (mini->status == APPEND)
		mini->status = PIPEAPPEND;
	else if (mini->status == HEREDOCAPPEND)
		mini->status = PIPEHEREDOCAPPEND;
	else if (mini->status == NONE)
		mini->status = PIPE;
}

void	append_status_regulator(t_mini *mini, int type)
{
	if (mini->status == NONE && type == APPEND)
		mini->status = APPEND;
	else if (mini->status == HEREDOC && type == APPEND)
		mini->status = HEREDOCAPPEND;
	else if (mini->status == APPEND && type == 0)
		mini->status = NONE;
	else if (mini->status == HEREDOCAPPEND && type == 0)
		mini->status = HEREDOC;
}

void	heredoc_status_regulator(t_mini *mini, int type)
{
	if (mini->status == NONE && type == HEREDOC)
		mini->status = HEREDOC;
	else if (mini->status == APPEND && type == HEREDOC)
		mini->status = HEREDOCAPPEND;
	else if (mini->status == HEREDOC && type == 0)
		mini->status = NONE;
	else if (mini->status == HEREDOCAPPEND && type == 0)
		mini->status = APPEND;
}

void	status_regulator(t_mini *mini, int i, int sq, int dq)
{
	while (mini->arg[i])
	{
		quote_check(mini->arg[i], &sq, &dq);
		if (if_input(mini, i, sq, dq))
			heredoc_status_regulator(mini, 0);
		if (if_heredoc(mini, i, sq, dq))
		{
			heredoc_status_regulator(mini, HEREDOC);
			i++;
		}
		if (if_output(mini, i, sq, dq))
			append_status_regulator(mini, 0);
		if (if_append(mini, i, sq, dq))
		{
			append_status_regulator(mini, APPEND);
			i++;
		}
		i++;
	}
}
