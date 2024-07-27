#include "../minishell.h"

void	child_procces(t_mini *cmd, char **command)
{
	cmd->pid = fork();
    if (cmd->pid == 0)
    {
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