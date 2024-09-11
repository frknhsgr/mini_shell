/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosgor <hosgor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:40 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/08 16:49:38 by hosgor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_arg_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	exit_with_error(t_mini *mini, char **arg)
{
	mini->status = 0;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_global_exit = 255;
	ft_free_dp(arg);
	ft_free_struct(mini);
	ft_free_dp(mini->env);
	exit (255);
}

int	exit_with_arg(t_mini *mini, int j, char **arg)
{
	if (j > 1)
	{
		if (!ft_isnumeric(arg[0]))
			exit_with_error(mini, arg);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_free_dp(arg);
		g_global_exit = 1;
		return (1);
	}
	if (j == 1)
	{
		if (!ft_isnumeric(arg[0]))
			exit_with_error(mini, arg);
		g_global_exit = ft_atoi(mini->flag_arg);
		ft_free_dp(arg);
		ft_free_struct(mini);
		ft_free_dp(mini->env);
		exit (g_global_exit);
	}
	return (0);
}

void	ft_exit(t_mini *mini, int i)
{
	char	**arg;
	int		j;

	j = 0;
	if (mini->flag_arg && mini->flag_arg[0])
	{
		arg = ft_split(mini->flag_arg, ' ');
		j = ft_arg_count(arg);
	}
	if (mini->cmd && i == 1)
	{
		printf("exit\n");
		if (mini->flag_arg && mini->flag_arg[0])
			if (exit_with_arg(mini, j, arg) == 1)
				return ;
		ft_free_dp(mini->env);
		ft_free_struct(mini);
		exit(g_global_exit);
	}
	ft_free_dp(arg);
}
