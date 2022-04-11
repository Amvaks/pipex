/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbart <sbart@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:35:48 by sbart             #+#    #+#             */
/*   Updated: 2022/03/13 18:36:10 by sbart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_getcount(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count + 1);
}

static int	ft_getnextlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			break ;
		s++;
		len++;
	}
	return (len);
}

static void	ft_free(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
}

static char	**ft_put(const char **s, char **p, int i, char c)
{
	int	j;
	int	nextlen;

	nextlen = ft_getnextlen(*s, c);
	p[i] = (char *)malloc(sizeof(char) * (nextlen + 1));
	if (!p[i])
	{
		p[i] = (void *)0;
		ft_free(p);
		return ((void *)0);
	}
	j = 0;
	while (j < nextlen)
	{
		p[i][j] = **s;
		j++;
		(*s)++;
	}
	p[i][j] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;

	if (!s)
		return ((void *)0);
	p = (char **)malloc(sizeof(char *) * (ft_getcount(s, c) + 1));
	if (!p)
		return ((void *)0);
	i = 0;
	while (*s)
	{
		p = ft_put(&s, p, i, c);
		if (!p)
			return ((void *)0);
		i++;
		if (*s)
			s++;
	}
	p[i] = (void *)0;
	return (p);
}
