/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:19:59 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/20 19:41:47 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	output_append_checker(t_mini *mini)
{
	if (mini->next != NULL && mini->append[0] == NULL \
	&& mini->output[0] == NULL)
		return (1);
	else if (mini->output[0] != NULL || mini->append[0] != NULL)
		return (2);
	return (0);
}

int	if_input(t_mini *mini, int j, int sq, int dq)
{
	if (mini->arg[j] == '<' && mini->arg[j + 1] != '<' && \
	sq % 2 == 0 && dq % 2 == 0)
		return (1);
	return (0);
}

int	if_heredoc(t_mini *mini, int j, int sq, int dq)
{
	if (mini->arg[j] == '<' && mini->arg[j + 1] == '<' && \
	sq % 2 == 0 && dq % 2 == 0)
		return (1);
	return (0);
}

int	if_output(t_mini *mini, int j, int sq, int dq)
{
	if (mini->arg[j] == '>' && mini->arg[j + 1] != '>' && \
	sq % 2 == 0 && dq % 2 == 0)
		return (1);
	return (0);
}

int	if_append(t_mini *mini, int j, int sq, int dq)
{
	if (mini->arg[j] == '>' && mini->arg[j + 1] == '>' && \
	sq % 2 == 0 && dq % 2 == 0)
		return (1);
	return (0);
}
