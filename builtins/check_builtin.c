/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:32 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/09 11:45:47 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	builtin_strcmp(char *s1, char *s2)
{
	if (check_same(s1, s2) == 0 || check_same(make_lower(s1), s2) == 0)
		return (0);
	return (1);
}

void	check_builtin(t_mini *mini, int i)
{
	if (mini->cmd && check_same(mini->cmd, "cd") == 0)
	{
		if (mini->flag_arg && mini->flag_arg[0])
			ft_takenewloc(mini);
		cd(mini, mini->flag_arg, NULL, NULL);
	}
	else if (mini->cmd && check_same(mini->cmd, "pwd") == 0)
		pwd();
	else if (mini->cmd && check_same(mini->cmd, "exit") == 0)
		ft_exit(mini, i);
	else if (mini->cmd && check_same(mini->cmd, "echo") == 0)
		ft_echo(mini);
	else if (mini->cmd && check_same(mini->cmd, "export") == 0)
		ft_export(mini);
	else if (mini->cmd && check_same(mini->cmd, "env") == 0)
		ft_env(mini, 8);
	else if (mini->cmd && check_same(mini->cmd, "unset") == 0)
		ft_unset(mini);
}

void	check_builtin_status(t_mini *mini)
{
	if (mini->cmd && check_same(mini->cmd, "exit") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && check_same(mini->cmd, "export") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && check_same(mini->cmd, "unset") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && check_same(mini->cmd, "cd") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && builtin_strcmp(mini->cmd, "env") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && builtin_strcmp(mini->cmd, "pwd") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && builtin_strcmp(mini->cmd, "echo") == 0)
		mini->status = BUILTIN;
}
