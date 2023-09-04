/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:00:05 by irgonzal          #+#    #+#             */
/*   Updated: 2023/08/29 19:47:42 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include <limits.h>

static size_t	ft_len_first_word(char const *s)
{
	size_t	i;

	i = 0;
    while (s[i] == ' ')
        i++;
	while (s[i] != ' ' && s[i] != '\0')
		i++;
	return (i);
}

static	char	**get_out(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
	return (NULL);
}

char	**separate_command(char const *s)
{
	char	**arr;
	size_t	len;

	arr = malloc(3 * sizeof(char *));
	if (!arr)
		return (NULL);
    len = ft_len_first_word(s);
    arr[0] = malloc((len + 1) * sizeof(char));
    arr[1] = malloc((ft_strlen(s) - len + 1) * sizeof(char));
    if (!arr[0] || !arr[1])
        return(get_out(arr));
    ft_memmove(arr[0], s, len);
    arr[0][len] = '\0';
    ft_memmove(arr[1], s + len, ft_strlen(s) - len);
    arr[1][ft_strlen(s)] = '\0';
	arr[2] = NULL;
	return (arr);
}

char *command_exists(char *s)
{
    char    *route;
    char    *path[10];
    int     i;

    if (s)
    {
        i = 0;
        path[0] = "/usr/local/bin/";
        path[1] = "/usr/bin/";
        path[2] = "/bin/";
        path[3] = "/usr/sbin/";
        path[4] = "/sbin/";
        path[5] = "/usr/local/share/dotnet/";
        path[6] = "/usr/local/munki/";
        path[7] =  "~/.dotnet/tools/"; 
        path[8] = "/Library/Frameworks/Mono.framework/Versions/Current/Commands/";
        path[9] = NULL;
        while (i < 7)
        {
            route = ft_strjoin(path[i], s);
            if (!route)
                return (NULL);
            //printf("route:[%s]\n", route);
            if (access(route, F_OK) == 0 && access(route, X_OK) == 0)
                return (route);
            free(route);
            i++;
        }
    }
    return (NULL);
}

int validation_files(int argc, char **argv)
{
    if (argc == 5)
    {
        if (access(argv[1], R_OK) == 0)
        {
            if (access(argv[4], W_OK) == 0)
                return (0);
        }
    }
    perror("Error");
    return (1);
}

int main(int argc, char **argv)
{
    int     fd[2];
    pid_t   childpid;
    char    *arguments_1[3];
    int     input_fd;
    int     output_fd;
    char    **command_1;
    char    **command_2;
    char    *arguments_2[3];

    command_1 = ft_split(argv[2], ' ');
    command_2 = ft_split(argv[3], ' ');
    if (validation_files(argc, argv) != 0 || !command_exists(command_1[0]))
        exit (1);
    //printf("Todo chachi\n");
    arguments_1[0] = command_1[0];
    arguments_1[1] = command_1[1];
    arguments_1[2] = NULL;
    arguments_2[0] = command_2[0];
    arguments_2[1] = command_2[1];
    arguments_2[2] = NULL;
    free(command_1);
    free(command_2);
    pipe(fd);
    childpid = fork();
    //printf("childpid 0: %d\n", childpid);
    if(childpid == -1)
    {
        perror("fork");
        exit(1);
    }
    if(childpid == 0)
    {
        input_fd = open(argv[1],O_RDONLY);
        //printf("childpid 1: %d\n", childpid);
        dup2(input_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        //printf("childpid 2: %d\n", childpid);
        close(fd[0]);
        if (execve(command_exists(arguments_1[0]), arguments_1, NULL) == -1)
            perror("execve1");
        //printf("childpid 3: %d\n", childpid);
        close(input_fd);
        exit(0);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        //printf("childpid 4: %d\n", childpid);
        output_fd = open(argv[4], O_WRONLY);
        //printf("[hi]\n");
        dup2(output_fd, STDOUT_FILENO);
        //printf("[hi2]\n");
        //printf("comando:[%s]\n", arguments_2[0]);
        //printf("ruta:[%s]\n", command_exists(arguments_2[0]));
        //printf("arguments_2: %s, %s\n", arguments_2[0], arguments_2[1]);
        //printf("childpid 5: %d\n", childpid);
        if (execve(command_exists(arguments_2[0]), arguments_2, NULL) == -1)
            perror("execve2");
        close(output_fd);
    }
    return(0);
}
/*
- validación de datos argc >= 5
- permisos de lectura y escritura en los archivos (access)
- permisos de ejecución de los comandos? (access x?)
- crear pipe, establece unos fd[0] y fd[1]
- crear proceso hijo fork() asignado en childprocess, que en el padre es != 0 y en el hijo es == 0
- establecer los pasos de cada proceso:
    - hijo, cierra fd[0] y ejecuta el primer comando sobre (read) input_file y lo escribe (write) en fd[1]
    - padre, cierra fd[1] y ejecuta el segundo comando sobre (read) fd[0] y escribe (write) sobre output_file
- leaks


*/