/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2023/11/12 13:24:50 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int is_local(char *s)
{
    int i;

    i = 0;
    if (s)
    {
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
    int i;
    char **var;

    i = 0;
    while (environ[i])
    {
        var = ft_super_split(environ[i], "=:");
        if (!var)
            return (-1);
        if (ft_strncmp(var[0], "PATH", 4) == 0)
        {
            ft_out(var, 100);
            return (i);
        }
        ft_out(var, 100);
        i++;
    }
    return (-1);
}

char *get_path(char *s, int i, char **path)
{
    char *route;
    char *folder;

    if (s && is_local(s) == 0)
        return (s);
    route = NULL;
    if (s && path && path[i])
    {
        folder = ft_strjoin(path[i], "/");
        if (folder)
        {
            route = ft_strjoin(folder, s);
            free(folder);
        }
    }
    return (route);
}

char *command_exists(char *s)
{
    char *route;
    int i;
    char **path;

    if (s)
    {
        if (is_local(s) == 0)
            return (s);
        i = 1;
        if (select_variable(environ) == -1)
            path = ft_super_split("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin", "=:");
        else
            path = ft_super_split(environ[select_variable(environ)], "=:");
        route = get_path(s, i, path);
        while (route != NULL)
        {
            if (access(route, F_OK) == 0 && access(route, X_OK) == 0)
            {
                ft_out(path, 100);
                return (route);
            }
            free(route);
            i++;
            route = get_path(s, i, path);
        }
        ft_out(path, 100);
    }
    return (NULL);
}
