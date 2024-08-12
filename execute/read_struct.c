#include "../minishell.h"

void	duplicate_default_fd(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	close_duplicate_fd(int fd[2])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	pipe_checker(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(127);
	}
}

int	output_append_checker(t_mini *mini)
{
	if (mini->next != NULL && mini->append[0] == NULL && mini->output[0] == NULL)
		return (1);
	else if (mini->output[0] != NULL || mini->append[0] != NULL)
		return (2);
	return (0);
}

int	ft_open_input(t_mini *mini, int i)
{
	int			fd;
	static int	j;

	if (!mini->input || !mini->input[j])
    	return (1);
	if (mini->input[j])
	{
		fd = open(mini->input[j], O_RDONLY, 0644);
        if (fd == -1 && (i != 1 || mini->status != BUILTIN))
            fderror_1(mini->input[j]);
        else if (fd == -1 && i == 1)
        {
            fderror_2(mini->input[j]);
            return (-1);
        }
        if (mini->input[j + 1])
            close (fd);
        j++;
	}
	if (mini->input[j] == NULL)
	{
		dup2(fd, 0);
		close(fd);
	}
	return (1);
}

int	ft_open_output(t_mini *mini, int i)
{
	int			fd;
    static int	j;

	fd = 0;
	if (!mini->output || !mini->output[j])
		return (1);
	if (mini->output[j])
	{
		fd = open(mini->output[j], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (fd == -1 && (i != 1 || mini->status != BUILTIN))
            fderror_1(mini->output[j]);
        else if (fd == -1 && i == 1)
		{
            fderror_2(mini->output[j]);
            return (-1);
        }
		if (mini->output[j + 1])
			close(fd);
		j++;
	}
	return (fd);
}

int	ft_open_append(t_mini *mini, int i)
{
	int			fd;
    static int	j;

	fd = 0;
	if (!mini->append || !mini->append[j])
		return (1);
	if (mini->append[j])
	{
		fd = open(mini->append[j], O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (fd == -1 && (i != 1 || mini->status != BUILTIN))
            fderror_1(mini->append[j]);
        else if (fd == -1 && i == 1)
        {
            fderror_2(mini->append[j]);
            return (-1);
        }
		if (mini->append[j + 1])
			close(fd);
		j++;
	}
	return (fd);
}

void	onecommand_output_input_regulator(t_mini *mini, int i, int sq, int dq)
{
	int	j;
	int	flag;
	int fd;

	j = -1;
	flag = 1;
	while (mini->arg[++j])
	{
		quote_check(mini->arg[j], &sq, &dq);
		if (flag == -1 || fd == -1)
			break ;
		if (mini->arg[j] == '<' && mini->arg[j + 1] != '<' && sq % 2 == 0 && dq % 2 == 0)
			flag = ft_open_input(mini, i);
		else if (mini->arg[j] == '<' && mini->arg[j + 1] == '<' && sq % 2 == 0 && dq % 2 == 0)
			j++;
		else if (mini->arg[j] == '>' && mini->arg[j + 1] != '>' && sq % 2 == 0 && dq % 2 == 0)
			fd = ft_open_output(mini, i);
		else if (mini->arg[j] == '>' && mini->arg[j + 1] == '>' && sq % 2 == 0 && dq % 2 == 0)
		{
			fd = ft_open_append(mini, i);
			j++;
		}
	}
	dup2(fd, 1);
	close (fd);
}

void	output_input_regulator(t_mini *mini, int i, int fd[2])
{
	close (fd[0]);
	if (output_append_checker(mini) == 1)
	{
		dup2(fd[1], 1);
		onecommand_output_input_regulator(mini, i, 0, 0);
	}
	else if (output_append_checker(mini) == 2)
		onecommand_output_input_regulator(mini, i, 0, 0);
}

void	execute_pipe(t_mini *mini, char **command, int i)
{
	int	pipe[2];

	pipe_checker(pipe);
	mini->pid = fork();
	if (mini->pid == 0)
	{
		close(pipe[0]);
		output_input_regulator(mini, i, pipe);
		close(pipe[1]);
		if (mini->status != BUILTIN)
			run_cmd(mini, command);
	}
	close(pipe[1]);
	dup2(pipe[0], 0);
	close(pipe[0]);
}

char **execve_command(t_mini *temp)
{
    char **ret;
    char **temp2;
    int i;

    i = 0;
    if (temp->flag_arg)
    {
        temp2 = ft_split(temp->flag_arg, ' ');
        while (temp2[i])
            i++;
    }
    else
        temp2 = NULL;
	if (temp->cmd != NULL)
		i++;
    ret = malloc(sizeof(char *) * (i + 1));
    if (!ret)
        return (NULL);
	if (temp->cmd != NULL)
    	ret[0] = ft_strdup(temp->cmd);
    i = 0;
    while (temp2 && temp2[i])
    {
        ret[i + 1] = ft_strdup(temp2[i]);
        i++;
    }
	if (i == 0 && temp->cmd == NULL)
    	ret[0] =  NULL;
	else
		ret[i + 1] = NULL;
	ft_free_dp(temp2);
    return (ret);
}

int	status_check(t_mini *temp)
{
	if (temp->status == PIPE || temp->status == PIPEAPPEND)
		return (1);
	else if (temp->status == HEREDOC || temp->status == HEREDOCAPPEND
		|| temp->status == PIPEHEREDOC || temp->status == PIPEHEREDOCAPPEND)
		return (2);
	else
		return (3);
}

void	close_heredoc()
{
	global_exit = 130;
	exit (130);
}

int	check_same(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 && ft_strncmp(s2, s1, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}

void	ft_heredoc(int fd[2], t_mini *mini, int fd_2[2])
{
	int		i;
	char	*temp;

	i = 0;
	dup2(fd[0], 0);
	while (mini->heredoc[i])
	{
		if (global_exit == 999)
		{
			free (temp);
			exit (130);
		}
		temp = readline("> ");
		if (!temp)
			close_heredoc();
		if (global_exit == 999)
			continue ;
		if (temp && mini->heredoc[i + 1] == NULL && check_same(mini->heredoc[i], temp) != 0)
			ft_putendl_fd(temp, fd_2[1]);
		if (check_same(mini->heredoc[i], temp) == 0)
			i++;
		free (temp);
	}
	exit (0);
}

void	heredoc_pipe(t_mini *mini, char **command, int fd[2])
{
	int	fd_2[2];
	int	status;

	pipe_checker(fd_2);
	mini->pid = fork();
	if (mini->pid == 0)
	{
		ft_heredoc(fd, mini, fd_2);
	}
	close(fd_2[1]);
	dup2(fd_2[0], 0);
	close(fd_2[0]);
	waitpid(mini->pid, &status, 0);
	if (WIFEXITED(status))
		global_exit = WEXITSTATUS(status);
	if (global_exit == 130)
		ft_free_dp(command);
}

void	ft_executer(t_mini *mini, char **command, int i, int fd[2])
{
	if (status_check(mini) == 1)
	{	
		if (mini->heredoc[0])
			heredoc_pipe(mini, command, fd);
		if (global_exit == 130)
			return ;
		execute_pipe(mini, command, i);
	}
	else if (status_check(mini) == 2)
	{
		heredoc_pipe(mini, command, fd);
		if (global_exit == 130)
			return ;
		execute_pipe(mini, command, i);
	}
	else
	{
		if (mini->heredoc[0])
			heredoc_pipe(mini, command, fd);
		if (global_exit == 130)
			return ;
    	child_procces(mini, command, i);
	}
}

void	read_and_exec(t_mini *cmd, int i)
{
    t_mini	*temp;
    char	**command;
	int		fd[2];

    temp = cmd;
	duplicate_default_fd(fd);
    while (temp)
    {
        command = execve_command(temp);
		ft_executer(temp, command, i, fd);
		ft_free_dp(command);
        temp = temp->next;
    }
	close_duplicate_fd(fd);
    wait_child(cmd);
}
