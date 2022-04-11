/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbart <sbart@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:38:14 by sbart             #+#    #+#             */
/*   Updated: 2022/03/13 20:47:15 by sbart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// https://github.com/chermensamec/pipex
// printenv -- sh, отобразить переменные окружения
// прочесть про fork на opennet. execve завершает процесс (вместо exit)?

//что по утечкам??

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5)) //while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_command(char **paths, char *cmd)
{
	char	*res;
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(res, X_OK)) // 0 -- какие права файла проверяются?
			return (res); //где-то дальше free
		free(res);
		paths++;
	}
	return (NULL);
}

void	second_process(char **argv, char **envp, char **paths, int *pipe_fd)
{
	char	*needed_path;
	char	**commands;
	int		fd;

	fd = open(argv[3], O_CREAT | O_WRONLY | O_TRUNC, 00777);
	if (fd < 0)
		ft_error(3);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fd[1]); //где он открывается? нужно ли переместить на 2 строки выше?
	commands = ft_split(argv[3], ' ');
	needed_path = find_command(paths, commands[0]);
	if (!needed_path)
	{
		free(needed_path);
		while (*commands)
			free(*commands++);
		free(commands);
		ft_error(4);
	}
	execve(needed_path, commands, envp);
	write(1, "TEST\n", 5); //выведется ли?
}

void	first_process(char **argv, char **envp, char **paths, int *pipe_fd)
{
	char	*needed_path;
	char	**commands;
	int		fd;
	//int		i;

	//i = 0;
	fd = open(argv[1], O_RDONLY); //нужно ли закрывать, если да, то где?
	if (fd < 0)
		ft_error(3);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	//почему в первом процессе pipe[1], а во втором pipe[0]
	close(pipe_fd[0]); //где он открывается? нужно ли переместить на 2 строки выше?
	commands = ft_split(argv[2], ' ');
	needed_path = find_command(paths, commands[0]);
	if (!needed_path)
	{
		free(needed_path);
		while (*commands)
			free(*commands++);
		free(commands);
		ft_error(4);
	}
	execve(needed_path, commands, envp); //???
		// execve(path, pars_com, envp);
		// close(fd[1]); 	//что и где закрывать? Если execve завершает процесс,
		//					то до этой строки не доходит, где тогда закрывается
		// free(path);
		// //while (pars_com[i])
		// //	free(pars_com[i++]);
		// free(pars_com);
		// ft_error(0);
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
	paths = (ft_split(find_path(envp), ':')); // не забыть free
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
	return (0);
}