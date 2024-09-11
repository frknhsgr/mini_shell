/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:41:59 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 13:41:46 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_business(char *str, t_mini *mini)
{
	char	*hold;
	char	*temp;

	take_name_for_export(delete_quotes(ft_strdup(str), mini, 0, 0), mini);
	temp = delete_quotes(ft_strdup(str), mini, 0, 0);
	hold = ft_substr(temp, mini->redirect->start, mini->redirect->len);
	free(temp);
	return (hold);
}

void	env_recent(char **envi, t_mini *mini)
{
	int	i;

	mini->env = malloc(sizeof(char *) * (count_environ(mini->env) + 2));
	i = 0;
	while (envi[i])
	{
		mini->env[i] = ft_strdup(envi[i]);
		i++;
	}
	mini->env[i] = NULL;
	free_env(envi);
}

void	free_env(char **envi)
{
	int	i;

	i = 0;
	while (envi[i])
	{
		free(envi[i]);
		envi[i] = NULL;
		i++;
	}
	free(envi);
}

void	put_env(char *str, t_mini *mini)
{
	int	d;

	env_recent(mini->env, mini);
	d = env_count_full(mini);
	mini->env[d] = ft_strdup(str);
	mini->env[d + 1] = NULL;
	free(str);
}

int	env_count_full(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i] && mini->env[i][0])
		i++;
	return (i);
}
