#include "../minishell.h"

int	open_output(t_mini *cmd)
{
	int fd_2;
    int c;

	c = 0;
	if (!cmd->output)
		return (1);
    while (cmd->output[c])
    {
        fd_2 = open(cmd->output[c], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (fd_2 == -1)
        {
            printf("minishell: %s: open error\n",cmd->output[c]);
            break;
        }
		if (cmd->output[c + 1])
			close (fd_2);
        c++;
    }
	return (fd_2);
}

int	open_append(t_mini *cmd)
{
	int fd_2;
    int c;

	c = 0;
	if (!cmd->append)
		return (1);
	while (cmd->append[c])
	{
		fd_2 = open(cmd->append[c], O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (fd_2 == -1)
        {
            printf("minishell: %s: open error\n",cmd->append[c]);
            break;
        }
		if (cmd->append[c + 1])
			close(fd_2);
		c++;
	}
	return (fd_2);
}

void set_input(t_mini *cmd)
{
	int fd_2;
    int c;

	c = 0;
    while (cmd->input[c])
    {
        fd_2 = open(cmd->input[c], O_RDONLY, 0644);
        if (fd_2 == -1)
        {
            printf("minishell: %s: No such file or directory\n",cmd->input[c]);
            exit(1);
        }
        c++;
    }
    dup2(fd_2, 0);
    close(fd_2);
}

void	non_pipe_output(t_mini *cmd)
{
	int	fd;


        if (cmd->status == APPEND)
		{
			fd = open_append(cmd);
			open_output(cmd);
		}
        else
		{
			fd = open_output(cmd);
			open_append(cmd);
		}
		dup2(fd, 1);
		close (fd);
}

void	child_procces(t_mini *cmd, char **command)
{
	cmd->pid = fork();
    if (cmd->pid == 0)
    {
        non_pipe_output(cmd);
		if (cmd->input[0])
        	set_input(cmd);
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