/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:47:48 by maquentr          #+#    #+#             */
/*   Updated: 2022/02/06 15:18:16 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd[2], char **av, char **envp)
{
	int		infile_fd;
	char	**mycmdargs;

	close(fd[0]);
	infile_fd = open(av[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		return (perror("Error "));
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
//	close(infile_fd); PEUT ETRE INUTILE CAR DUP CLOSE TOUT SEUL 
//	close(fd[1]);
	mycmdargs = ft_split(av[2], ' ');
	if (mycmdargs == NULL)
		exit(1);
	get_path(envp, mycmdargs);
	ft_error(mycmdargs, infile_fd);
}

void	parent_process(int ac, char **av, char **envp, int fd[2])
{
	int		outfile_fd;
	char	**mycmdargs;

	mycmdargs = ft_split(av[3], ' ');
	if (mycmdargs == NULL)
		exit(1);
	close(fd[1]);
	outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		return (perror("Error "));
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(fd[0]);
	get_path(envp, mycmdargs);
	ft_error(mycmdargs, outfile_fd);
}

void	*get_path(char *envp[], char **mycmdargs)
{
	int		j;
	char	*paths;
	char	**mypaths;

	if (mycmdargs[0][0] == '/')
	{
		execve(mycmdargs[0], mycmdargs, envp);
		ft_cmd_err(mycmdargs);
	}
	j = 0;
	while (envp[j] && !(ft_strnstr(envp[j], "PATH=", 5)))
		j++;
	if (envp[j] == NULL)
		return (NULL);
	paths = envp[j] + 5;
	mypaths = ft_split(paths, ':');
	if (!(mypaths))
		return (NULL);
	while_instruc(mypaths, paths, mycmdargs, envp);
	ft_free_double_tab(mypaths);
	return (NULL);
}

void	pipex(int ac, char **av, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	status = 0;
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
		close_and_wait(fd, status, child1, child2);
	}
	else
		perror("ERROR: invalid number of arguments");
}

int	main(int ac, char **av, char **envp)
{
	if (av[2][0] == '\0' || av[3][0] == '\0')
	{
		write(2, "cmd not found\n", 14);
		return (1);
	}
	if ((envp == NULL) || (*envp == NULL))
		(perror("ERROR :"));
	av = parsing_front_spaces(av);
	pipex(ac, av, envp);
	return (0);
}
