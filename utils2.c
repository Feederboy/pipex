/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:54:53 by maquentr          #+#    #+#             */
/*   Updated: 2022/02/05 18:58:19 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_double_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_cmd_err(char **mycmdargs)
{
	ft_putstr_fd("pipex : cmd not found : ", 2);
	ft_putstr_fd(mycmdargs[0], 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

void	while_instruc(char **mypaths, char *paths,
		char **mycmdargs, char **envp)
{
	int	i;

	i = -1;
	while (mypaths[++i])
	{
		paths = ft_join(mypaths[i], "/");
		paths = ft_join(paths, mycmdargs[0]);
		execve(paths, mycmdargs, envp);
		free(paths);
		paths = NULL;
	}
}

void	close_and_wait(int fd[2], int status, pid_t child1, pid_t child2)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
