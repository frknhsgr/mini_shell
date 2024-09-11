/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:35 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/10 20:17:07 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_control(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_flag_control(char **arg, int *i)
{
	if (flag_control(arg[*i] + 1) == 1)
		return ;
	*i += 1;
	if (arg[*i] && arg[*i][0] == '-')
		echo_flag_control(arg, i);
}

void	echo_with_arg(t_mini *mini)
{
	char	**arg;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	arg = ft_split(mini->flag_arg, ' ');
	if (arg[i][0] == '-')
		echo_flag_control(arg, &i);
	flag = i;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (!flag && arg[flag])
		printf("\n");
	ft_free_dp(arg);
}

void	ft_echo(t_mini *mini)
{
	if (mini->flag_arg && mini->flag_arg[0])
	{
		echo_with_arg(mini);
	}
	else
		printf("\n");
}
