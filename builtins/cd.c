#include "../minishell.h"

char	*get_oldpwd(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (check_same(mini->env[i], "OLDPWD=") == 0)
			return (ft_strdup(ft_strchr(mini->env[i], '=') + 1));
		i++;
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	global_exit = 1;
	return (NULL);
}

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

void	set_newlocation(char *oldpwd, char **newpwd, char *newlocation)
{
	char	*tmp;

	tmp = ft_strjoin(oldpwd, "/");
	*newpwd = ft_strjoin(tmp, newlocation);
	free (tmp);
}

char	*get_home(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (check_same(mini->env[i], "HOME=") == 0)
			return (ft_strdup(ft_strchr(mini->env[i], '=') + 1));
		i++;
	}
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	global_exit = 1;
	return (NULL);
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
	global_exit = 1;
	return (1);
}

void	set_newpwd2(char *newpwd, char **newpwd2)
{
	int	i;

	i = ft_strlen(newpwd) - 1;
	if (i > 2 && newpwd[i] == '.' && newpwd[i - 1] == '.' && newpwd[i - 2] == '/')
		*newpwd2 = getcwd(NULL, 0);
	else
		*newpwd2 = NULL;
}

void	set_newpwd(t_mini *mini, char *newpwd, char *newpwd2, int i)
{
	char	*tmp;

	if (newpwd2 == NULL)
		tmp = ft_strjoin("PWD =", newpwd);
	else
		tmp = ft_strjoin("PWD =", newpwd2);
	free (mini->env[i]);
	mini->env[i] = ft_strdup(tmp);
	free (tmp);
}

void	set_oldpwd(t_mini *mini, char *oldpwd, int i)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD =", oldpwd);
	free (mini->env[i]);
	mini->env[i] = ft_strdup(tmp);
	free (tmp);
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
		printf("case1\n");
		if (cd_case1(mini, &newlocation, &newpwd, oldpwd) == 1)
			return ;
	}
	else if (newlocation && newlocation[0] != '/')
	{
		printf("set_newlocation\n");
		set_newlocation(oldpwd, &newpwd, newlocation);
	}
	if (newlocation == NULL)
	{
		printf("case2\n");
		if (cd_case2(mini, &newpwd, &newlocation, oldpwd) == 1)
			return ;
	}
	printf("%s\n", newpwd);
	if (chdir(newpwd) != 0)
	{
		printf("chdir situation\n");
		if (chdir_situation(newpwd, newlocation, oldpwd) == 1)
			return ;
	}
	set_pwd(mini, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	global_exit = 0;
}