/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/10/14 13:47:33 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>
/*
static void    ft_leaks(void)
{
    system("leaks pipex");
}
*/

static int run_first_command(char **argv)
{
    char    **command;

    //printf("comando 1\n");
    command = ft_super_split(argv[2], " ");
    if (!command)
        return (-1);
    return (execve(get_path(command[0], command_exists(command[0])), command, environ) == -1);
}

static int run_second_command(char **argv)
{
    char    **command;

    command = ft_super_split(argv[3], " ");
    /*
    int i = 0;
    while (command[i])
    {
        printf("%d:%s\n", i, command[i]);
        i++;
    }
    */
    if (!command)
        return (-1);
    //printf("holaaaa\n");
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
        ///printf("2 hijo\n");
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        aux_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (aux_fd < 0)
            return (-1);
        //printf("hola comando 2\n");
        dup2(aux_fd, STDOUT_FILENO);
        return (run_second_command(argv));
        /*
        if (run_second_command(argv) == -1)
            perror(NULL);
        close(aux_fd);
        exit (0);*/
    }
    else
    {
        close(fd[0]);
        aux_fd = open(argv[1],O_RDONLY);
        if (aux_fd < 0)
        {
            perror(NULL);
            exit(1);
        }
        dup2(aux_fd, STDIN_FILENO);
        //printf("childpid 1\n");
        dup2(fd[1], STDOUT_FILENO);
        //return (run_first_command(argv) == -1);
        if (run_first_command(argv) == -1)
            perror("error 1");
        printf("hola\n");
        close(aux_fd);
        exit (0);
    }
    return (0);
}

int main(int argc, char **argv)
{
    pid_t   childpid;
    //char    *arg[]={"/bin/echo", "$PATH", NULL};

    //atexit(ft_leaks);
    /*if (execve("/bin/echo", arg) == -1)
        perror("exec");*/
    /*int i = 0;
    while (i < argc)
    {
        printf("i %d: %s\n",i, argv[i]);
        i++;
    }*/
    /*
    char    **command;

    command = ft_super_split(argv[3], " ");
    
    int i = 0;
    while (command[i])
    {
        printf("%d:%s\n", i, command[i]);
        i++;
    }*/
    //exit(0);
    if (argc != 5)//validation(argc, argv) != 0)
        exit (1);
    childpid = fork();
    //printf("antes %d\n", childpid);
    if(childpid == -1)
    {
        perror(NULL);
        exit(1);
    }
    if(childpid == 0)
    {
        if (child_proccess(argv) == -1)
        {
            perror(NULL);
            printf("hay errores\n");
            exit(1);
        }
    }
    if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
    {
        if (WIFSIGNALED(childpid) == 1)
        {
            printf("sig: %d\n", WIFSIGNALED(childpid));
            perror(NULL);
            exit(1);
        }
        exit (0);
    }
}

/*
Cosas que arreglar:

- comparar subjects y revisar la gestión de errores
- norminette
*/