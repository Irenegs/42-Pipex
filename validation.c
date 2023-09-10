/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:36:54 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/10 22:43:43 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

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
            free_list(var);
            return (i);
        }
        free_list(var);
        i++;
    }
    free_list(var);
    return (-1);
}

char    *get_path(char *s, int i, char **envp)
{
    char    **path;
    char    *route;
    char    *folder;

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
        free_list(path);
    }
    return (route);
}

int command_exists(char *s, char **envp)
{
    char    *route;
    int     i;

    if (s)
    {
        i = 1;
        route = get_path(s, i, envp);
        while (route != NULL)
        {
            if (access(route, F_OK) == 0 && access(route, X_OK) == 0)
            {
                free(route);
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
            if (access(argv[4], W_OK) == 0)
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
            if (c1 && command_exists(c1[0], envp) != -1)
            {
                if (c2 && command_exists(c2[0], envp) != -1)
                {
                    free_list(c1);
                    free_list(c2);
                    return (0);
                }
            }
        }
    }
    free_list(c1);
    free_list(c2);
    perror("Error 1");
    return (1);
}
