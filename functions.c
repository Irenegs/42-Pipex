/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:46:33 by irgonzal          #+#    #+#             */
/*   Updated: 2023/11/30 21:50:47 by irgonzal         ###   ########.fr       */
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

char	**ft_out(char **arr, int i)
{
	int	j;

	j = 0;
	while (j <= i && arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}
