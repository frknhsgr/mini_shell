/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:24:05 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/03 18:24:06 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_mini *mini, int status)
{
	int	i;

	i = 0;
	if (!mini->env)
		return ;
	while (mini->env[i])
	{
		if (status == 1)
			printf("declare -x ");
		printf("%s\n", mini->env[i]);
		i++;
	}
}
