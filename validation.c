/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/02 18:58:43 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

static char    *get_path(int i)
{
    char    *path[10];

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
    return (path[i]);
}

char    *command_exists(char *s)
{
    char    *route;
    int     i;

    if (s)
    {
        i = 0;
        while (i < 7)
        {
            route = ft_strjoin(get_path(i), s);
            if (!route)
                return (NULL);
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
    return (1);
}

int validation(int argc, char **argv, char *c1[3], char *c2[3])
{
    if (validation_files(argc, argv) == 0)
    {
        if (c1 && command_exists(c1[0]))
        {
            if (c2 && command_exists(c2[0]))
                    return (0);
        }
    }
    perror("Error");
    return (1);
}