/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/10/29 12:52:47 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>

static int run_first_command(char **argv)
{
    char    **command;

    command = ft_super_split(argv[2], " ");
    if (!command)
        return (-1);
    return (execve(get_path(command[0], command_exists(command[0])), command, environ));
}

static int run_second_command(char **argv)
{
    char    **command;

    command = ft_super_split(argv[3], " ");
    if (!command)
        return (-1);
    return (execve(get_path(command[0], command_exists(command[0])), command, environ) == -1);
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
        if (run_second_command(argv) == -1)
        {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        //exit(EXIT_FAILURE);
    }
    else
    {
        close(fd[0]);
        aux_fd = open(argv[1],O_RDONLY);
        if (aux_fd < 0)
        {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        dup2(aux_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        if (run_first_command(argv) == -1)
            perror(NULL);
        close(aux_fd);
        //exit (EXIT_SUCCESS);//quitar?
    }
    return (0);
}

int main(int argc, char **argv)
{
    pid_t   childpid;

    if (argc != 5)
        exit (EXIT_FAILURE);
    childpid = fork();
    if(childpid == -1)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    if(childpid == 0)
    {
        if (child_proccess(argv) == -1)
        {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    }
    if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
    {
        if (WIFSIGNALED(childpid) == 1)
            exit(EXIT_FAILURE);
        perror(NULL);
        exit(EXIT_SUCCESS);
    }
}

/*
- probar fallos de malloc
- fsanitize y leaks
- environ cuando es null -> mirar cómo se gestiona
- mirar si al no tener bad address cuando el comando no existe, da command not found
- códigos de error en casos 5 y 6, 127 y 126.
- norminette
*/