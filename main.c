/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:47:48 by maquentr          #+#    #+#             */
/*   Updated: 2022/01/13 15:27:32 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process(int fd[2], char **av, char **envp)
{
	int i;
	char **cmd;
	char **mypaths;
	int infile_fd;
	char **mycmdargs;


	close(fd[0]);
	infile_fd = open(av[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		printf("no such file or directory\n");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	close(fd[1]);
	cmd = get_args(av);
	mycmdargs = ft_split(av[2], ' ');
	mypaths = get_path(envp);
	i = -1;
	while (mypaths[++i])
	{
		cmd[i] = ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
		execve(cmd[i], mycmdargs, envp); //add perror("ERROR") to debug
	}
}
void parent_process(int ac, char **av, char **envp, int fd[2])
{
	int	outfile_fd;
	char **cmd;
	char **mypaths;
	int i;
	char **mycmdargs;

	mycmdargs = ft_split(av[3], ' ');

	close(fd[1]);
	outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		printf("No such file or directoty\n");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(fd[1]);
	close(fd[0]);
	cmd = get_args(av);
	mypaths = get_path(envp);
	i = -1;
	while (mypaths[++i])
	{
		cmd[i] = ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
		execve(cmd[i], mycmdargs, envp); //add perror("ERROR") to debug
	}
}

char	**get_path(char *envp[])
{
	int i;
	int j;
	char *paths;
	char **mypaths;

	j = -1;
	while (envp[++j])
	{
		if (ft_strnstr(envp[j], "PATH=", 9999))
			break;
	}
	paths = envp[j];

	paths = ft_substr(paths, 5, ft_strlen(paths));
	mypaths = ft_split(paths, ':');

	i = 0;
	i = -1;
	while (mypaths[++i]) //adding '/' at the end of the path for it to work correctly
	{
		mypaths[i] = ft_join(mypaths[i], "/");
	}
	i = -1;
	free(paths);
	return (mypaths);
}

char **get_args(char **av)
{
	char **mycmdargs;


	mycmdargs = ft_split(av[2], ' '); //split bugged if no entry given
	
	return (mycmdargs);
}

int main(int ac, char **av, char **envp)
{
	int fd[2];
	int pid;


	if (ac == 5)
	{
		if (pipe(fd) == -1)
			perror("ERROR WHILE CALLING PIPE");
		pid = fork();
		if (pid == -1)
			perror("ERROR WHILE CALLING FORK");
		if (pid == 0)
			child_process(fd, av, envp);
		else
			parent_process(ac, av, envp, fd);
	}
	else
		perror("ERROR: check arguments\nusage: .pipex <infile> <cmd1> <cmd2> <outfile>");
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
