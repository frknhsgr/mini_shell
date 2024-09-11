/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:15:50 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/09 09:35:45 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	take_flag_arg(t_mini *mini, char *str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		mini->flag_arg = ft_substr(str, i, ft_strlen(str) - i);
}
