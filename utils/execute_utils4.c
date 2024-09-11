/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:31:48 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 16:28:49 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_for_structs(t_mini *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->redirect)
		{
			free (temp->redirect);
			temp->redirect = NULL;
		}
		if (temp->utils)
		{
			free (temp->utils);
			temp->utils = NULL;
		}
		if (i > 0)
			free (temp);
		temp = temp->next;
		i++;
	}
}

void	ft_free_struct(t_mini *mini)
{
	t_mini	*temp;

	temp = mini;
	while (mini)
	{
		if (mini->cmd || (mini->cmd && mini->cmd[0]))
			free(mini->cmd);
		if (mini->flag_arg && mini->flag_arg[0])
			free(mini->flag_arg);
		if (mini->input)
			ft_free_dp(mini->input);
		if (mini->append)
			ft_free_dp(mini->append);
		if (mini->output)
			ft_free_dp(mini->output);
		if (mini->heredoc)
			ft_free_dp(mini->heredoc);
		if (mini->arg)
		{
			free(mini->arg);
			mini->arg = NULL;
		}
		mini = mini->next;
	}
	ft_free_for_structs(temp);
}

int	status_check2(t_mini *mini)
{
	t_mini	*temp;

	temp = mini;
	while (temp)
	{
		if (status_check(temp) == 2)
			return (1);
		temp = temp->next;
	}
	return (0);
}
