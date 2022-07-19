/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbart <sbart@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:50:32 by sbart             #+#    #+#             */
/*   Updated: 2022/03/26 16:50:44 by sbart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_numstr(const char *str, char c)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (*str)
	{
		if (*str != c && f == 0)
		{
			f = 1;
			i++;
		}
		else if (*str == c)
			f = 0;
		str++;
	}
	return (i);
}

char	*ft_getstr(char const *s, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (0);
	while (start < end)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_free(char **res, int n)
{
	int	i;

	i = 0;
	while (i != n)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

int	ft_help(char ***res, char const *s, char c)
{
	if (!s)
		return (0);
	*res = malloc(sizeof(char *) * (ft_numstr(s, c) + 1));
	if (!*res)
		return (0);
	return (1);
}	

char	**ft_split(char const *s, char c)
{
	int		end;
	int		start;	
	int		i;
	char	**res;

	end = 0;
	start = -1;
	i = 0;
	if (!ft_help(&res, s, c))
		return (0);
	while (end <= ft_strlen(s))
	{
		if (s[end] != c && start < 0)
			start = end;
		else if ((s[end] == c || end == ft_strlen(s)) && start >= 0)
		{	
			res[i] = ft_getstr(s, start, end);
			if (!res[i++])
				return (ft_free(res, i - 1));
			start = -1;
		}
		end++;
	}
	res[i] = 0;
	return (res);
}
