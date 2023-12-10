/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:46:33 by irgonzal          #+#    #+#             */
/*   Updated: 2023/12/10 18:11:32 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	select_errorcode(int exit, int part, char **argv)
{
	char	**command;
	char	*cmd;
	int		error;

	if (exit == 255 || exit == 0 || exit == 127)
	{	
		if (access(argv[part + 2 * (part - 1)], F_OK) != 0 && part != 2)
			return (2);
		if (access(argv[part + 2 * (part - 1)], R_OK) != 0)
			return (13);
		command = ft_super_split(argv[part + 1], " ");
		if (!command)
			return (-1);
		cmd = command_exists(command[0]);
		if (access(cmd, F_OK) != 0 && is_local(command[0]) != 0)
			error = 127;
		else if (access(cmd, X_OK) != 0)
			error = 126;
		else if (access(argv[4], W_OK) != 0)
			error = 1;
		else
			error = 0;
		if (is_local(command[0]) != 0)
			free(cmd);
		ft_out(command);
		return (error);
	}
	return (0);
}

int	write_error(int error)
{
	if (error == 127)
		ft_putstr_fd("Command not found\n", 2);
	else if (error != 0)
		perror(NULL);
	return (error);
}

char	**ft_out(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

int	is_local(char *s)
{
	int	i;

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
