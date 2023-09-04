/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:11 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/02 18:00:32 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <stdio.h> 
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <limits.h>

char *command_exists(char *s);
int validation_files(int argc, char **argv);
//int    get_command(char *s, char *arr[3]);
int validation(int argc, char **argv, char *c1[3], char *c2[3]);
#endif