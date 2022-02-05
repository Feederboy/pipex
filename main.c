/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:47:48 by maquentr          #+#    #+#             */
/*   Updated: 2022/02/05 17:57:59 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


//METTRE MYPATHS ET OPEN LES FD DANS LE MAIN ET LES BALANCER APRES VERIF DANS LES FCT

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_check_access(char **cmd, char **mypaths, char **mycmdargs)
{
	int i;
	int j;
	char **tmp;

	tmp = cmd;
	j = -1;
	while(cmd[++j]) //USE FONCTION ACCESS POUR CHECK SI LA CMD EXIST ET LENVOYER A EXECVE
	{
		i = -1;
		while (mypaths[++i])
		{
			tmp[j] = ft_join(mypaths[i], mycmdargs[0]); //protect ft_join
			if (access(cmd[j], X_OK) == 0)
			{
				//			free(tmp[j]);
				return 1;
			}
		}
		//	free(tmp[j]);
	}
	return 0;
}

void	ft_error(char **mycmdargs, int fd)
{
	int i;

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

void child_process(int fd[2], char **av, char **envp)
{
	int infile_fd;
	char **mycmdargs;

	close(fd[0]);
	infile_fd = open(av[1], O_RDONLY, 0777); //add protection
	if (infile_fd == -1)
		return (perror("Error "));
	dup2(fd[1], STDOUT_FILENO); //add protection
	dup2(infile_fd, STDIN_FILENO); //add protection

	mycmdargs = ft_split(av[2], ' ');
	if (mycmdargs == NULL)
		exit(EXIT_FAILURE);
	get_path(envp, mycmdargs);
	ft_error(mycmdargs, infile_fd);
}

void parent_process(int ac, char **av, char **envp, int fd[2])
{
	int	outfile_fd;
	char **mycmdargs;


	mycmdargs = ft_split(av[3], ' ');
	if (mycmdargs == NULL)
		exit(EXIT_FAILURE);
	close(fd[1]);
	outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777); //add protection
	if (outfile_fd == -1)
		return (perror("Error "));
	dup2(fd[0], STDIN_FILENO); //add protection
	dup2(outfile_fd, STDOUT_FILENO); //add protection
	close(outfile_fd);
	close(fd[0]);
	get_path(envp, mycmdargs);
	ft_error(mycmdargs, outfile_fd);
}

void	ft_free_double_tab(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}


void	*get_path(char *envp[], char **mycmdargs)
{
	int i;
	int j;
	char *paths;
	char **mypaths;

	if (mycmdargs[0][0] == '/')
	{
		execve(mycmdargs[0], mycmdargs, envp);
		ft_putstr_fd("pipex : cmd not found : ", 2);
		ft_putstr_fd(mycmdargs[0], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	j = -1;
	while (envp[++j])
	{
		if (ft_strnstr(envp[j], "PATH=", 5))
			break;
	}
	paths = envp[j] + 5; //removing "PATH=" from the string
	mypaths = ft_split(paths, ':');
	if (!(mypaths))
		return (NULL);
	i = -1;
	while (mypaths[++i]) //adding '/' at the end of the path for it to work correctly
	{
		paths = ft_join(mypaths[i], "/");
		paths = ft_join(paths, mycmdargs[0]);
		execve(paths, mycmdargs, envp);
		free(paths);
		paths = NULL;
	}
	ft_free_double_tab(mypaths);
	return (NULL);
}

char **get_args(char **av)
{
	char **mycmdargs;

	mycmdargs = ft_split(av[2], ' ');
	if (!(mycmdargs = ft_split(av[2], ' ')))	//split bugged if no entry given
		exit(write(2, "Error split\n", 12));
	return (mycmdargs);
}

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


int	main(int ac, char **av, char **envp)
{
	if (av[2][0] == '\0' || av[3][0] == '\0')
	{
		write(2, "cmd not found\n", 14);
		return 1;
		//	exit(EXIT_FAILURE);
	}
	if ((envp == NULL) || (*envp == NULL))
		perror("ERROR :");
	av = parsing_front_spaces(av);
	printf("AV[2] = %s   av[3] = %s\n", av[2], av[3]);
	pipex(ac, av, envp);
	return (0);
}
