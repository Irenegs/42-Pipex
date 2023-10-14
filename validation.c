/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2023/10/14 12:53:02 by irgonzal         ###   ########.fr       */
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
    int i;

    i = 0;
    if (s)
    {
        //printf("s: %s", s);
        while (s[i] != '\0')
        {
            if (s[i] == '/')
                return (0);
            i++;
        }
    }
    return (1);
}

static int select_variable(char **environ)
{
    int     i;
    char    **var;

    i = 0;
    while (environ[i])
    {
        var = ft_super_split(environ[i], "=:");
        if (!var)
            return (-1);
        if (ft_strncmp(var[0], "PATH", 4) == 0)
        {
            ft_out(var,100);
            return (i);
        }
        ft_out(var,100);
        i++;
    }
    //ft_out(var,100);//se puede borrar?
    return (-1);
}

char    *get_path(char *s, int i)
{
    char    **path;
    char    *route;
    char    *folder;

    //printf("PATH:%s\n"[2]);
    if (s && is_local(s) == 0)
        return (s);
    route = NULL;
    if (s && select_variable(environ) != -1)
    {
        path = ft_super_split(environ[select_variable(environ)], "=:");
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


int command_exists(char *s)
{
    char    *route;
    int     i;

    if (s)
    {
        //printf("command exists\n");
        if (is_local(s) == 0 && access(s, F_OK) == 0 && access(s, X_OK) == 0)
            return (0);
        i = 1;
        route = get_path(s, i);
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
            route = get_path(s, i);
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

int validation(int argc, char **argv)
{
    char    **c1;
    char    **c2;

    //if (c1 && c2)
    //{
    if (argc == 5 && validation_files(argc, argv) == 0)
    {
        //printf("files ok\n");
        c1 = ft_split(argv[2], ' ');
        if (c1 && command_exists(c1[0]) != -1)
        {
            //printf("c1 ok\n");
            c2 = ft_split(argv[3], ' ');
            if (c2 && command_exists(c2[0]) != -1)
            {
                ft_out(c1, 100);
                ft_out(c2, 100);
                return (0);
            }
            ft_out(c2, 100);
        }
        ft_out(c1, 100);
    }
    //}
    //write(2, perror(""), ft_strlen(strerror(perror(""))));
    perror(NULL);
    return (1);
}
