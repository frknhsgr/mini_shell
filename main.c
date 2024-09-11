/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:23:54 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 16:52:08 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global_exit;

void	ft_close(t_mini *mini)
{
	ft_free_dp(mini->env);
	printf("exit\n");
	exit(0);
}

int	ft_split_arg(t_mini *mini, char *temp, char *temp2, char **temp3)
{
	ft_signal_regulator(MAIN_P);
	temp = readline("minishell> ");
	if (!temp)
		ft_close(mini);
	add_history(temp);
	temp2 = ft_strtrim(temp, " \t");
	free(temp);
	if (!temp2[0])
	{
		free(temp2);
		return (0);
	}
	ft_signal_regulator(MAIN_P2);
	if (!is_quotes_closed(temp2) || \
	!is_valid_name(temp2, mini, 0, 0) || !pipe_check(temp2))
		return (free(temp2), ft_free_for_structs(mini), 0);
	*temp3 = is_dollar_exist_and_valid(temp2, mini, 0, 0);
	if (!*temp3[0])
	{
		free(*temp3);
		ft_free_for_structs(mini);
		return (0);
	}
	return (1);
}

void	ft_start(t_mini *mini, char **args, char *temp3)
{
	while (1)
	{
		if (!ft_split_arg(mini, NULL, NULL, &temp3))
			continue ;
		args = mm_split(temp3, '|');
		placing(args, mini, 0);
		read_and_exec(mini, command_list_count(mini));
		ft_free_dp(args);
	}
}

int	main(int ac, char **av)
{
	t_mini	mini;

	(void)av;
	mini.env = NULL;
	g_global_exit = 0;
	if (ac != 1)
	{
		ft_putstr_fd("Error: Too Many Arguments!\n", 2);
		return (0);
	}
	take_env(&mini);
	ft_start(&mini, NULL, NULL);
}
