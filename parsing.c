/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:35:43 by maquentr          #+#    #+#             */
/*   Updated: 2022/01/20 15:10:40 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **parsing_front_spaces(char **av)
{
	int i;
	int j;

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

