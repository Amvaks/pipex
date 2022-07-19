/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbart <sbart@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:44:17 by sbart             #+#    #+#             */
/*   Updated: 2022/03/26 16:51:10 by sbart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int tag)
{
	if (tag == 0)
	{
		perror("Incorrect number of arguments");
		exit(1);
	}
	else if (tag == 1)
		perror("Pipe creating error");
	else if (tag == 2)
		perror("Fork creating error");
	else if (tag == 3)
	{
		perror("The file cannot be opened");
		exit(1);
	}
	else if (tag == 4)
	{
		perror("Command not found");
		exit(127);
	}
	exit(errno);
}

void	ft_free_array_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		free(strings[i++]);
	free(strings);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
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
		if (!access(res, X_OK))
			return (res);
		free(res);
		paths++;
	}
	return (NULL);
}
