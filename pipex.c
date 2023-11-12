/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/11/12 18:30:21 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

static void write_error_and_exit(int error)
{
    if (error != 1)
        ft_putstr_fd("./pipex: ", 2);
    if (error == 13)
    {
        ft_putstr_fd("command not found", 2);
        exit(127);
    }
    else
        perror(NULL);
    exit(1);
}


static int run_command(char **argv, int i)
{
    char    **command;
    char    *cmd;

    command = ft_super_split(argv[i + 1], " ");
    if (!command)
        return (-1);
    cmd = command_exists(command[0]);
    if (!cmd)
        return (-1);
    return (execve(cmd, command, environ));
}

static int child_proccess(char **argv)
{
    int     fd[2];
    pid_t   childpid;
    int     aux_fd;

    pipe(fd);
    childpid = fork();
    if(childpid == -1)
        return (-1);
    if(childpid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        aux_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (aux_fd < 0)
            return (-1);
        dup2(aux_fd, STDOUT_FILENO);
        return (run_command(argv, 2));
    }
    else
    {
        close(fd[0]);
        aux_fd = open(argv[1],O_RDONLY);
        if (aux_fd < 0)
            return (-1);
        dup2(aux_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        return (run_command(argv, 1));
    }
    return (-1);
}

int main(int argc, char **argv)
{
    pid_t   childpid;
    int     childexit;

    if (argc != 5)
        exit (1);
    childpid = fork();
    if (childpid == -1)
        write_error_and_exit(1);
    if (childpid == 0)
    {
        childexit = child_proccess(argv);
        if (childexit != 0)
        {
            if (childexit == -1)
                write_error_and_exit(1);
            return(1);
        }
    }
    if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
    {
        if (WIFSIGNALED(childpid) == 1)
        {
            write_error_and_exit(WTERMSIG(childpid));
        }
    }
    exit(errno);
}

/*
- probar fallos de malloc./
- fsanitize y leaks
- mirar si al no tener bad address cuando el comando no existe, da command not found
- códigos de error en casos 5 y 6, 127 y 126.
- norminette
*/