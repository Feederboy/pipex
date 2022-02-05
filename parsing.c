/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:35:43 by maquentr          #+#    #+#             */
/*   Updated: 2022/02/05 18:59:10 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parsing_front_spaces(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[2][j] && av[2][j] == ' ')
	{
		i++;
		j++;
	}
	av[2] = av[2] + i;
	i = 0;
	j = 0;
	while (av[3][j] && av[3][j] == ' ')
	{
		i++;
		j++;
	}
	av[3] = av[3] + i;
	return (av);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_error(char **mycmdargs, int fd)
{
	int	i;

	i = -1;
	ft_putstr_fd("pipex : cmd not found : ", 2);
	ft_putstr_fd(mycmdargs[0], 2);
	ft_putstr_fd("\n", 2);
	while (mycmdargs[++i])
		free(mycmdargs[i]);
	free(mycmdargs);
	close(fd);
	exit(0);
}
