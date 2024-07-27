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

void	output_regulator(t_mini *cmd, int fd[2], int i)
{
	close(fd[0]);
	if (cmd->next != NULL && cmd->append == NULL && cmd->output == NULL)
		dup2(fd[1], 1);
}

void	execute_pipe(t_mini *mini, char **command)
{
	int	pipe[2];

	pipe_checker(pipe);
	mini->pid = fork();
	if (mini->pid == 0)
	{
		close(pipe[0]);
		output_regulator(mini, pipe, 0);
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
    ret = malloc(sizeof(char *) * (i + 2));
    if (!ret)
        return (NULL);
    ret[0] = ft_strdup(temp->cmd);
    i = 0;
    while (temp2 && temp2[i])
    {
        ret[i + 1] = ft_strdup(temp2[i]);
        i++;
    }
    ret[i + 1] =  NULL;
	ft_free_dp(temp2);
    return (ret);
}

void read_and_exec(t_mini *cmd)
{
    t_mini	*temp;
    char	**run;
	int		fd[2];

    temp = cmd;
	duplicate_default_fd(fd);
    while (temp)
    {
        run = execve_command(temp);
		if (temp->status == PIPE)
			execute_pipe(temp, run);
		else if (temp->status == NONE)	
        	child_procces(temp, run);
        temp = temp->next;
    }
	close_duplicate_fd(fd);
    wait_child(cmd);
}
