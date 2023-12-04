/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:53:11 by irgonzal          #+#    #+#             */
/*   Updated: 2023/12/03 10:25:46 by irgonzal         ###   ########.fr       */
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
char	*command_exists(char *s);
char	**ft_super_split(char const *s, char *sep);
char	**ft_out(char **arr);
int		write_error(int error);
int		is_separator(char c, char *sep);
int		is_escaped(char const *s, int i);
int		new_word(char const *s, char *sep, int i, int quotes);
int		ft_wc(char const *s, char *sep);
int		end_word(char const *s, char *sep, int i, int quot);
int		is_local(char *s);
#endif
