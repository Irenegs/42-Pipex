/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:46:33 by irgonzal          #+#    #+#             */
/*   Updated: 2023/12/04 23:12:25 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_error(int error)
{
	if (error == 127)
		ft_putstr_fd("Command not found\n", 2);
	else
		perror(NULL);
	exit(error);
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
