#include "../minishell.h"

int	cd_case1(t_mini *mini, char **newlocation, char **newpwd, char *oldpwd)
{
	*newpwd = get_oldpwd(mini);
	if (!*newpwd)
	{
		free (oldpwd);
		return (1);
	}
	*newlocation = *newpwd;
	return (0);
}

int	cd_case2(t_mini *mini, char **newpwd, char **newlocation, char *oldpwd)
{
	*newpwd = get_home(mini);
	if (!*newpwd)
	{
		free(oldpwd);
		return (1);
	}
	*newlocation = *newpwd;
	return (0);
}

int	chdir_situation(char *newpwd, char *newlocation, char *oldpwd)
{
	if (!ft_isdirectory(newpwd))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newlocation, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (!(is_fileordirectory(newpwd)))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newlocation, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(newpwd, X_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newlocation, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(newpwd);
	free(oldpwd);
	g_global_exit = 1;
	return (1);
}

void	set_pwd(t_mini *mini, char *oldpwd, char *newpwd)
{
	char	*newpwd2;
	int		i;

	i = 0;
	set_newpwd2(newpwd, &newpwd2);
	while (mini->env[i])
	{
		if (check_same(mini->env[i], "PWD=") == 0)
			set_newpwd(mini, newpwd, newpwd2, i);
		if (check_same(mini->env[i], "PWD=") == 0)
			set_oldpwd(mini, oldpwd, i);
		i++;
	}
	if (newpwd2 != NULL)
		free(newpwd2);
}

void	cd(t_mini *mini, char *newlocation)
{
	char	*oldpwd;
	char	*newpwd;

	if (newlocation && newlocation[0] == '/')
		newpwd = ft_strdup(newlocation);
	oldpwd = getcwd(NULL, 0);
	if (newlocation && check_same(newlocation, "-") == 0)
	{
		if (cd_case1(mini, &newlocation, &newpwd, oldpwd) == 1)
			return ;
	}
	else if (newlocation && newlocation[0] != '/')
		set_newlocation(oldpwd, &newpwd, newlocation);
	if (newlocation == NULL)
		if (cd_case2(mini, &newpwd, &newlocation, oldpwd) == 1)
			return ;
	if (chdir(newpwd) != 0)
		if (chdir_situation(newpwd, newlocation, oldpwd) == 1)
			return ;
	set_pwd(mini, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	g_global_exit = 0;
}
