/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:47:48 by maquentr          #+#    #+#             */
/*   Updated: 2021/12/23 18:52:37 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void child_process(int f1, char *cmd1)
{
}

void parent_process(int f2, char *cmd2)
{
}

void pipex(int f1, int f2)
{
	int fd[2];
	pid_t parent;

	pipe(fd); // a proteger
	parent(fork);
	if (parent < 0)
		return (perror("Fork: "));

	if (parent == 0)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}
*/

int main(int ac, char **av, char **envp)
{
	(void)ac;
	char *path_from_envp;
	char **mypaths;
	char **mycmdargs;
	int len = ft_strlen(envp[4]);
	path_from_envp = ft_substr(*envp, 1, len); //a completer ; substr n'est peut etre pas la meilleure fct pour aller choper le path. A mediter
		printf("envp = %s\n", path_from_envp);
	mypaths = ft_split(path_from_envp, ':'); // as for splitting the envp path, print out the result of your split and have a look. Add / at the end for the path to work correctly
	mycmdargs = ft_split(av[2], ' ');

	return (0);
}


















/*
int main(int ac, char **av)
{
	int fd[2];
	int child1;
	int child2;

	(void)ac;
	pipe(fd);
	if (pipe(fd) == -1)
		return (-1);
	child1 = fork();
	if (child1 < 0)
		return (1);
	if (child1 == 0) //child process 1 always get id 0, parent get child id. so here it's child1
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("cat", "cat", "signature.txt", NULL);
	}
	child2 = fork();
	if (child2 < 0)
		return (2);
	if (child2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		printf("AV3 = %s\n", av[3]);
		execlp("grep", av[0], "des", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}

*/



/*
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork : "));
	if (child2 == 0)
	{
		//child process 2 fonction
		child_two();
*/
