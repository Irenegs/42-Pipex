/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2023/10/03 18:43:36 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
/*
static void free_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
*/

int is_local(char *s)
{
    if (s)
    {
        if (ft_strncmp(s, "./", 2) == 0 || ft_strncmp(s, "/", 1) == 0 || ft_strncmp(s, "../", 3) == 0)
        {
            if (access(s, F_OK) == 0 && access(s, X_OK) == 0)
                return (0);
            else
                return (-1);
        }
    }
    return (1);
}

static int select_variable(char **envp)
{
    int     i;
    char    **var;

    i = 0;
    while (envp[i])
    {
        var = ft_super_split(envp[i], "=:");
        if (!var)
            return (-1);
        if (ft_strncmp(var[0], "PATH", 4) == 0)
        {
            ft_out(var,1000);
            return (i);
        }
        ft_out(var,1000);
        i++;
    }
    //printf("var %d\n", i);
    ft_out(var,1000);//se puede borrar?
    return (-1);
}

char    *get_path(char *s, int i, char **envp)
{
    char    **path;
    char    *route;
    char    *folder;

    //printf("PATH:%s\n", envp[2]);
    if (s && is_local(s) == 0)
        return (s);
    route = NULL;
    if (s && select_variable(envp) != -1)
    {
        path = ft_super_split(envp[select_variable(envp)], "=:");
        if (!path)
            return (NULL);
        if (path[i])
        {
            folder = ft_strjoin(path[i], "/");
            if (folder)
            {
                route = ft_strjoin(folder, s);
                free(folder);
            }
        }
        //printf("get path\n");
        ft_out(path, 100);
        //printf("after free\n");
    }
    return (route);
}


int command_exists(char *s, char **envp)
{
    char    *route;
    int     i;

    if (s)
    {
        //printf("command exists\n");
        if (is_local(s) < 1)
            return (is_local(s));
        i = 1;
        route = get_path(s, i, envp);
        while (route != NULL)
        {
            //printf("i:[%d-%s]\n", i, route);
            if (access(route, F_OK) == 0 && access(route, X_OK) == 0)
            {
                free(route);
                //printf("ret i:[%d]\n", i);
                return (i);
            }
            free(route);
            i++;
            route = get_path(s, i, envp);
        }
    }
    return (-1);
}

static int validation_files(int argc, char **argv)
{
    if (argc == 5)
    {
        if (access(argv[1], R_OK) == 0)
        {
            if (access(argv[4], F_OK) != 0 || access(argv[4], W_OK) == 0)
                return (0);
        }
    }
    return (1);
}

int validation(int argc, char **argv, char **envp)
{
    char    **c1;
    char    **c2;

    c1 = ft_split(argv[2], ' ');
    c2 = ft_split(argv[3], ' ');
    if (c1 && c2)
    {
        if (argc == 5 && validation_files(argc, argv) == 0)
        {
            //printf("files ok\n");
            if (c1 && command_exists(c1[0], envp) != -1)
            {
                //printf("c1 ok\n");
                if (c2 && command_exists(c2[0], envp) != -1)
                {
                    if (c1)
                        ft_out(c1, 1000);
                    if (c1)
                        ft_out(c2, 1000);
                    return (0);
                }
            }
        }
    }
    if (c1)
        ft_out(c1, 1000);
    if (c2)
        ft_out(c2, 1000);
    perror("Error 1");
    return (1);
}
