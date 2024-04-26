/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:11 by irgonzal          #+#    #+#             */
/*   Updated: 2023/12/28 18:54:44 by irgonzal         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

extern char	**environ;
int		is_local(char *s);
int		select_errorcode(int exit, int part, char **argv);
int		write_error(int error);
char	**ft_out(char **arr);
char	**ft_super_split(char const *s, char *sep);
int		is_separator(char c, char *sep);
int		is_escaped(char const *s, int i);
int		new_word(char const *s, char *sep, int i, int quotes);
int		ft_wc(char const *s, char *sep);
int		end_word(char const *s, char *sep, int i, int quot);
char	*command_exists(char *s);

#endif
