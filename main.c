/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:47:48 by maquentr          #+#    #+#             */
/*   Updated: 2022/01/19 18:36:47 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void free_all(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}
*/
void child_process(int fd[2], char **av, char **envp)
{
	int i;
	char **cmd;
	char **mypaths;
	int infile_fd;
	char **mycmdargs;

	close(fd[0]);
	infile_fd = open(av[1], O_RDONLY, 0777); //add protection
//	if (infile_fd == -1)
//		return (perror("Error "));
	if (av[2] == NULL)
		exit(EXIT_FAILURE);
	dup2(fd[1], STDOUT_FILENO); //add protection
	dup2(infile_fd, STDIN_FILENO); //add protection
	close(infile_fd);
	close(fd[1]);
	cmd = ft_split(av[2], ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	mycmdargs = ft_split(av[2], ' ');
	if (mycmdargs == NULL)
		exit(EXIT_FAILURE);
	mypaths = get_path(envp);
	if(!(mypaths))
		exit(EXIT_FAILURE);
	int j;
	j = -1;
	while(cmd[++j])
	{
		i = -1;
		while (mypaths[++i])
		{
			cmd[j] = ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
			execve(cmd[j], mycmdargs, envp); //add perror("ERROR") to debug
		}
	}

	/*
	i = -1;
	while (mypaths[++i])
	{
			cmd[i] = ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
			execve(cmd[i], mycmdargs, envp); //add perror("ERROR") to debug
	}
	*/
}
void parent_process(int ac, char **av, char **envp, int fd[2])
{
	int	outfile_fd;
	char **cmd;
	char **mypaths;
	int i;
	char **mycmdargs;


	if (av[3] == NULL)
		exit(EXIT_FAILURE);
	mycmdargs = ft_split(av[3], ' ');
	if (mycmdargs == NULL)
		exit(EXIT_FAILURE);
	close(fd[1]);
	outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777); //add protection
//	if (outfile_fd == -1)
//		return (perror("Error "));
	dup2(fd[0], STDIN_FILENO); //add protection
	dup2(outfile_fd, STDOUT_FILENO); //add protection
	close(outfile_fd);
	close(fd[1]);
	close(fd[0]);
	cmd = ft_split(av[3], ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	mypaths = get_path(envp);
	if (!(mypaths))
		exit(EXIT_FAILURE);

	int j;
	j = -1;
	while(cmd[++j])
	{
		i = -1;
		while (mypaths[++i])
		{
			cmd[j] = ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
			execve(cmd[j], mycmdargs, envp); //add perror("ERROR") to debug
		}
	}
			
/*
	i = -1;
	while (mypaths[++i]) //ICI ON VA TROP LOIN DANS CMD DOU LE HEAP BUFFER OVERFLOW
	{
				cmd[i]= ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
				execve(cmd[i], mycmdargs, envp); //add perror("ERROR") to debug
	}
*/


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
		if (ft_strnstr(envp[j], "PATH=", 5))
			break;
	}
	paths = envp[j] + 5; //removing "PATH=" from the string
	if (!(mypaths = ft_split(paths, ':')))
			exit(EXIT_FAILURE);
	i = -1;
	while (mypaths[++i]) //adding '/' at the end of the path for it to work correctly
	{
		mypaths[i] = ft_join(mypaths[i], "/");
		printf("paths[i] = %s\n", mypaths[i]);
	}
	return (mypaths);
}

char **get_args(char **av)
{
	char **mycmdargs;

	if (!(mycmdargs = ft_split(av[2], ' ')))	//split bugged if no entry given
		exit(EXIT_FAILURE);
	return (mycmdargs);
}

/*
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
*/
void pipex(int ac, char **av, char **envp)
{
	int fd[2];
	int status;
	pid_t child1;
	pid_t child2;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			perror("Error:");
		child1 = fork();
		if (child1 < 0)
			return (perror("Fork: "));
		if (child1 == 0)
			child_process(fd, av, envp);
		child2 = fork();
		if (child2 < 0)
			return (perror("Fork: "));
		if (child2 == 0)
			parent_process(ac, av, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(child1, &status, 0);
		waitpid(child2, &status, 0);
	}
	else
		perror("ERROR: check arguments\nusage: .pipex <infile> <cmd1> <cmd2> <outfile>");
}

int main(int ac, char **av, char **envp)
{
	pipex(ac, av, envp);
	return (0);
}
