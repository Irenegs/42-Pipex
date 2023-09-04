/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex-ultimate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:00:05 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/02 19:06:33 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int main(int argc, char **argv)
{
    int     fd[2];
    pid_t   childpid;
    int     input_fd;
    int     output_fd;
    char    **command_1;
    char    **command_2;
    
    command_1 = ft_split(argv[2], ' ');
    command_2 = ft_split(argv[3], ' ');
    if (validation(argc, argv, command_1, command_2) != 0)
        exit (1);
    pipe(fd);
    childpid = fork();
    if(childpid == -1)
    {
        perror("fork");
        exit(1);
    }
    if(childpid == 0)
    {
        input_fd = open(argv[1],O_RDONLY);
        dup2(input_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        if (execve(command_exists(command_1[0]), command_1, NULL) == -1)
            perror("execve1");
        close(input_fd);
        exit(0);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        output_fd = open(argv[4], O_WRONLY);
        dup2(output_fd, STDOUT_FILENO);
        if (execve(command_exists(command_2[0]), command_2, NULL) == -1)
            perror("execve2");
        close(output_fd);
    }
    free(command_1);
    free(command_2);
    return(0);
}
/*
- leaks
- norminette
*/