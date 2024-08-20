/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:42 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/20 18:15:43 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_newpwd2(char *newpwd, char **newpwd2)
{
	int	i;

	i = ft_strlen(newpwd) - 1;
	if (i > 2 && newpwd[i] == '.' && \
	newpwd[i - 1] == '.' && newpwd[i - 2] == '/')
		*newpwd2 = getcwd(NULL, 0);
	else
		*newpwd2 = NULL;
}

void	set_newpwd(t_mini *mini, char *newpwd, char *newpwd2, int i)
{
	char	*tmp;

	if (newpwd2 == NULL)
		tmp = ft_strjoin("PWD=", newpwd);
	else
		tmp = ft_strjoin("PWD=", newpwd2);
	free (mini->env[i]);
	mini->env[i] = ft_strdup(tmp);
	free (tmp);
}

char	*get_oldpwd(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD=", 7) == 0)
			return (ft_strdup(ft_strchr(mini->env[i], '=') + 1));
		i++;
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	g_global_exit = 1;
	return (NULL);
}

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_global_exit = 0;
}
