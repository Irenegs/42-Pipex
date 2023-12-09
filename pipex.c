/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/12/09 15:57:53 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exiting(int exit1, int error, char **argv)
{
	char	**command;
	char	*cmd;

	command = NULL;
	if (exit1 != 0)
	{
		ft_putstr_fd(strerror(exit1), 2);
		ft_putstr_fd("\n", 2);
	}
	if (error == 255 || error == 0 || error == 127)
	{
		command = ft_super_split(argv[3], " ");
		if (!command)
			return (-1);
		cmd = command_exists(command[0]);
		if (access(cmd, F_OK) != 0)
			write_error(127);
		else if (access(cmd, X_OK) != 0)
			write_error(126);
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
	{
		ft_out(command);
		return (127);
	}
	execve(cmd, command, environ);
	ft_out(command);
	return (-1);
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

int	main(int argc, char **argv)
{
	pid_t	childpid1;
	pid_t	childpid2;
	int		fd[2];
	int		aux_fd;

	if (argc != 5)
		exit (1);
	pipe(fd);
	childpid1 = fork();
	childpid2 = fork();
	if (childpid1 == -1 || childpid2 == -1)
		exit(write_error(1));
	if (childpid1 != 0 && childpid2 == 0)
	{
		aux_fd = open(argv[1], O_RDONLY);
		if (aux_fd < 0)
			return (-1);
		manage_pipe(1, fd[0], fd[1], aux_fd);
		return (run_command(argv, 1));
	}
	else if (childpid1 == 0 && childpid2 != 0)
	{
		aux_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (aux_fd < 0)
			return (-2);

		manage_pipe(2, fd[0], fd[1], aux_fd);
		return (run_command(argv, 2));
	}
	close (fd[1]);
	if (waitpid(-1, &childpid1, 0) != -1 && waitpid(-1, &childpid2, 0) != -1)
	{
		exiting(WEXITSTATUS(childpid1), WEXITSTATUS(childpid2), argv);
	}
	exit(0);
}

/*
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
		aux_fd = open(argv[1], O_RDONLY);
		if (aux_fd < 0)
			return (-1);
		manage_pipe(1, fd[0], fd[1], aux_fd);
		return (run_command(argv, 1));
	}
	else if (waitpid(-1, &childpid, WIFEXITED(childpid)) != -1)
	{
		aux_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (aux_fd < 0)
			return (-2);
		manage_pipe(2, fd[0], fd[1], aux_fd);
		run_command(argv, 2);
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
	else if (waitpid(-1, &childpid, 0) != -1)
		exiting(WEXITSTATUS(childpid), argv);
	printf("Adios\n");
}
*/