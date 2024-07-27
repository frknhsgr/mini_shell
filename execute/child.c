#include "../minishell.h"

void non_pipe_output(t_mini *cmd)
{
    int fd_2;
    int c;

        if (cmd->append[0] || cmd->output[0])
        {
            
            c = 0;
            while (cmd->output[c])
            {
                fd_2 = open(cmd->output[c], O_WRONLY | O_TRUNC | O_CREAT, 0644);
                if (fd_2 == -1)
                {
                    printf("minishell: %s: open error\n",cmd->output[c]);
                    break;
                }
                c++;
            }
            dup2(fd_2, 1);
            close(fd_2);
        }
        if (cmd->input[0])
        {
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
}

void	child_procces(t_mini *cmd, char **command)
{
	cmd->pid = fork();
    if (cmd->pid == 0)
    {
        non_pipe_output(cmd);
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