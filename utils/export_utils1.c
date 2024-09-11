/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:46:32 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 14:47:11 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_err_msg(char	*str, int status)
{
	if (status == 0)
		ft_putstr_fd("minishell: export: ", 2);
	else
		ft_putstr_fd("minishell: unset: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	free (str);
}

void	take_name_for_export(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	mini->redirect->start += i;
	mini->redirect->len = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			mini->redirect->len += 1;
			break ;
		}
		i++;
		mini->redirect->len += 1;
	}
	free(str);
}

int	does_env_have(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(str, mini->env[i], ft_strlen(str)))
			return (i);
		i++;
	}
	return (0);
}

int	export_unset_control(int *control)
{
	if ((*control) == 1)
	{
		(*control) = 0;
		return (1);
	}
	else
		return (0);
}

void	make_it_short(t_mini *mini, char **keep, int *i)
{
	export_err_msg(delete_quotes(ft_strdup(keep[(*i)]), mini, 0, 0), 0);
	g_global_exit = 1;
	(*i)++;
}
