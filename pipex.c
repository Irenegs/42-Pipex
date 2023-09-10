/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/10 23:15:25 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>

static int run_first_command(char **argv, char **envp, int fd[2])
{
    char    **command;
    int     aux_fd;
    
    aux_fd = open(argv[1],O_RDONLY);
    if (aux_fd < 0)
        return(-1);
    dup2(aux_fd, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    command = ft_split(argv[2], ' ');
    if (!command)
        return (-1);
    if (execve(get_path(command[0], command_exists(command[0], envp), envp), command, envp) == -1)
        close(aux_fd);
    return (-1);    
}

static int run_second_command(char **argv, char **envp, int fd[2])
{
    char    **command;
    int     aux_fd;

    dup2(fd[0], STDIN_FILENO);
    aux_fd = open(argv[4], O_WRONLY | O_TRUNC);
    if (aux_fd < 0)
    {
        perror("Error");
        exit(1);
    }
    dup2(aux_fd, STDOUT_FILENO);
    command = ft_split(argv[3], ' ');
    if (!command)
        return (-1);
    if (execve(get_path(command[0], command_exists(command[0], envp), envp), command, envp) == -1)
        close(aux_fd);
    return (-1);
}

static int child_proccess(char **argv, char **envp)
{
    int     fd[2];
    pid_t   childpid;

    pipe(fd);
    childpid = fork();
    if (childpid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (childpid == 0)
    {
        if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
        {
            close(fd[1]);
            if (run_second_command(argv, envp, fd) == -1)
                perror("exec2");
            exit (0);
        }
    }
    else 
    {
        close(fd[0]);
        if (run_first_command(argv, envp, fd) == -1)
            perror("exec1");
        exit (0);
    }
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    pid_t   childpid;

    if (validation(argc, argv, envp) != 0)
        return (1);
    childpid = fork();
    if (childpid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (childpid == 0)
    {
        if (child_proccess(argv, envp) == -1)
            exit(1);
    }
    if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
        exit (0);
}

/*
./pipex a.txt "sleep 10" "ls" b.txt

*/