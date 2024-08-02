#include "../minishell.h"

int	open_output(t_mini *cmd, int i)
{
	int fd_2;
    int j;

	j = 0;
	if (!cmd->output)
		return (1);
    while (cmd->output[j])
    {
        fd_2 = open(cmd->output[j], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (fd_2 == -1 && (i != 1 || cmd->status != BUILTIN))
            fderror_1(cmd->output[j]);
        else if (fd_2 == -1 && i == 1)
        {
            fderror_2(cmd->output[j]);
            return (fd_2);
        }
		if (cmd->output[j + 1])
			close (fd_2);
        j++;
    }
	return (fd_2);
}

int	open_append(t_mini *cmd, int i)
{
	int fd_2;
    int j;

	j = 0;
	if (!cmd->append)
		return (1);
	while (cmd->append[j])
	{
		fd_2 = open(cmd->append[j], O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (fd_2 == -1 && (i != 1 || cmd->status != BUILTIN))
            fderror_1(cmd->append[j]);
        else if (fd_2 == -1 && i == 1)
        {
            fderror_2(cmd->append[j]);
            return (-1);
        }
		if (cmd->append[j + 1])
			close(fd_2);
		j++;
	}
	return (fd_2);
}

int set_input(t_mini *cmd, int i)
{
	int fd_2;
    int j;

	j = 0;
    if (!cmd->input || !cmd->input[0])
        return (-1);
    while (cmd->input[j])
    {
        fd_2 = open(cmd->input[j], O_RDONLY, 0644);
        if (fd_2 == -1 && (i != 1 || cmd->status != BUILTIN))
            fderror_1(cmd->input[j]);
        else if (fd_2 == -1 && i == 1)
        {
            fderror_2(cmd->input[j]);
            return (fd_2);
        }
        if (cmd->input[j + 1])
            close (fd_2);
        j++;
    }
    dup2(fd_2, 0);
    close(fd_2);
    return (fd_2);
}

int	non_pipe_output(t_mini *cmd, int i)
{
	int	fd;

    if (cmd->status == APPEND)
	{
		fd = open_append(cmd, i);
        if (fd == -1)
            return (-1);
		open_output(cmd, i);
	}
    else
	{
		fd = open_output(cmd, i);
        if (fd == -1)
            return (-1);
		open_append(cmd, i);
	}
	dup2(fd, 1);
	close (fd);
    return (fd);
}

void	child_procces(t_mini *cmd, char **command, int i)
{
	cmd->pid = fork();
    if (cmd->pid == 0)
    {
        set_input(cmd, i);
        non_pipe_output(cmd, i);
        run_cmd(cmd, command);
        exit(0);
    }
    return ;
}


void wait_child(t_mini *cmd)
{
    t_mini *temp;

    temp = cmd;
    while (temp)
    {
        waitpid(temp->pid, 0, 0);
        temp = temp->next;
    }
}