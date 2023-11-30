/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/11/30 22:10:50 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exiting(int error, char **argv)
{
	char	**command;
	char	*cmd;

	command = NULL;
	if (error == 13)
	{
		command = ft_super_split(argv[3], " ");
		if (!command)
			return (-1);
		cmd = command_exists(command[0]);
		if (access(cmd, F_OK) != 0)
			exit (127);
		else if (access(cmd, X_OK) != 0)
			exit (126);
		else if (access(argv[4], W_OK) != 0)
			exit (1);
		else
			exit (0);
	}
	exit(error);
}

static int	run_command(char **argv, int i)
{
	char	**command;
	char	*cmd;

	command = ft_super_split(argv[i + 1], " ");
	if (!command)
		return (-1);
	cmd = command_exists(command[0]);
	if (!cmd)
		return (127);
	return (execve(cmd, command, environ));
}

static void	manage_pipe(int part, int fd_0, int fd_1, int aux_fd)
{
	if (part == 1)
	{
		close(fd_0);
		dup2(aux_fd, STDIN_FILENO);
		dup2(fd_1, STDOUT_FILENO);
	}
	else
	{
		close(fd_1);
		dup2(fd_0, STDIN_FILENO);
		dup2(aux_fd, STDOUT_FILENO);
	}
}

static int	child_proccess(char **argv)
{
	int		fd[2];
	pid_t	childpid;
	int		aux_fd;

	pipe(fd);
	childpid = fork();
	if (childpid == -1)
		return (-1);
	if (childpid == 0)
	{
		aux_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (aux_fd < 0)
			return (-2);
		manage_pipe(2, fd[0], fd[1], aux_fd);
		return (run_command(argv, 2));
	}
	else
	{
		aux_fd = open(argv[1], O_RDONLY);
		if (aux_fd < 0)
			return (-1);
		manage_pipe(1, fd[0], fd[1], aux_fd);
		return (run_command(argv, 1));
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	pid_t	childpid;
	int		childexit;

	if (argc != 5)
		exit (1);
	childpid = fork();
	if (childpid == -1)
		exit(write_error(1));
	if (childpid == 0)
	{
		childexit = child_proccess(argv);
		if (childexit != 0)
			write_error(childexit);
	}
	if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
	{
		if (WIFSIGNALED(childpid) == 1)
			exiting(WTERMSIG(childpid), argv);
		exit(0);
	}
}
