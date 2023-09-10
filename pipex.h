/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:11 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/10 09:13:50 by irgonzal         ###   ########.fr       */
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

int command_exists(char *s, char **envp);
//int validation_files(int argc, char **argv);
int    get_command(char *s, char *arr[3], char **envp);
int validation(int argc, char **argv, char **envp);
char    *get_path(char *s, int i, char **envp);
char	**ft_super_split(char const *s, char *sep);
#endif