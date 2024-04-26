/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:34 by irgonzal          #+#    #+#             */
/*   Updated: 2023/12/28 19:35:00 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exiting(int exitcode, int part, char **argv)
{
	int	error;

	error = select_errorcode(exitcode, part, argv);
	if (error == 255)
		write_error(13);
	else
		write_error(error);
	if (part == 2)
	{
		if (error == 255 || error == -1)
			exit(127);
		exit(error);
	}
	return (0);
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

static int	piping(int part, int fd_0, int fd_1, char **argv)
{
	int		aux_fd;

	if (part == 1)
		aux_fd = open(argv[1], O_RDONLY);
	else
		aux_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (aux_fd < 0)
		return (-1);
	manage_pipe(part, fd_0, fd_1, aux_fd);
	return (run_command(argv, part));
}

int	main(int argc, char **argv)
{
	pid_t	childpid1;
	pid_t	childpid2;
	int		fd[2];

	if (argc != 5)
		exit (1);
	pipe(fd);
	childpid1 = fork();
	childpid2 = fork();
	if (childpid1 == -1 || childpid2 == -1)
		exit(write_error(1));
	if (childpid1 != 0 && childpid2 == 0)
		piping(1, fd[0], fd[1], argv);
	else if (childpid1 == 0 && childpid2 != 0)
		piping(2, fd[0], fd[1], argv);
	close (fd[1]);
	if (waitpid(-1, &childpid1, 0) != -1 && waitpid(-1, &childpid2, 0) != -1)
	{
		exiting(WEXITSTATUS(childpid1), 1, argv);
		exiting(WEXITSTATUS(childpid2), 2, argv);
	}
	exit(0);
}
