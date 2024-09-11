/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:21 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/09 11:44:23 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "HOME=", 5) == 0)
			return (ft_strdup(ft_strchr(mini->env[i], '=') + 1));
		i++;
	}
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	g_global_exit = 1;
	return (NULL);
}

void	set_oldpwd(t_mini *mini, char *oldpwd, int i)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	free (mini->env[i]);
	mini->env[i] = ft_strdup(tmp);
	free (tmp);
}

void	set_newlocation(char *oldpwd, char **newpwd, char *newlocation)
{
	char	*tmp;

	tmp = ft_strjoin(oldpwd, "/");
	*newpwd = ft_strjoin(tmp, newlocation);
	free (tmp);
}

int	ft_isfile(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

void	ft_takenewloc(t_mini *mini)
{
	char	*temp;
	int		i;

	i = 0;
	while (mini->flag_arg[i] && mini->flag_arg[i] != ' ')
		i++;
	temp = ft_substr(mini->flag_arg, 0, i);
	free (mini->flag_arg);
	mini->flag_arg = temp;
}
