/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbart <sbart@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:38:14 by sbart             #+#    #+#             */
/*   Updated: 2022/03/26 16:51:07 by sbart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_process(char **argv, char **envp, char **paths, int *pipe_fd)
{
	char	*needed_path;
	char	**commands;
	int		fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 00777);
	if (fd < 0)
		ft_error(3);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fd[1]);
	commands = ft_split(argv[3], ' ');
	needed_path = find_command(paths, commands[0]);
	if (!needed_path)
	{
		free(needed_path);
		ft_free_array_strings(commands);
		close(pipe_fd[1]);
		ft_error(4);
	}
	execve(needed_path, commands, envp);
}

void	first_process(char **argv, char **envp, char **paths, int *pipe_fd)
{
	char	*needed_path;
	char	**commands;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error(3);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	commands = ft_split(argv[2], ' ');
	needed_path = find_command(paths, commands[0]);
	if (!needed_path)
	{
		free(needed_path);
		ft_free_array_strings(commands);
		close(pipe_fd[1]);
		ft_error(4);
	}
	execve(needed_path, commands, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid[2];
	int		pipe_fd[2];
	char	**paths;

	if (argc != 5)
		ft_error(0);
	if (pipe(pipe_fd) < 0)
		ft_error(1);
	paths = (ft_split(find_path(envp), ':'));
	pid[0] = fork();
	if (pid[0] < 0)
		ft_error(2);
	if (pid[0] == 0)
		first_process(argv, envp, paths, pipe_fd);
	pid[1] = fork();
	if (pid[1] < 0)
		ft_error(2);
	if (pid[1] == 0)
		second_process(argv, envp, paths, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[0], NULL, 0);
	ft_free_array_strings(paths);
	return (0);
}
