/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:47:48 by maquentr          #+#    #+#             */
/*   Updated: 2022/01/04 15:46:55 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void child_one_process(int fd, char **mypaths, char *cmd1)
{
	int i;
	char *cmd;

	i = -1;
	while (mypaths[++i])
	{
		cmd = ft_join(mypaths[i], cmd1); //protect ft_join
		execve(cmd, mycmdargs, envp); //add perror("ERROR") to debug
		free(cmd);
	}

}

void parent_process(int f2, char *cmd2)
{
}

void pipex(char **envp, char **mycmdargs, char **mypaths)
{
	int fd[2];
	int status;
	pid_t child1;
	pid_t child2;


	pipe(fd); // a proteger
	child1 = fork;
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}
*/


//ENVOYER FD, AV ET ENVP DANS LES FCT AUXILLIAIRES ET TRAITER LA BAS LA MERDE
//
//
//
//
//
int main(int ac, char **av, char **envp)
{
	char *path_from_envp;
	char **mypaths;
	char **mycmdargs;
	int len = ft_strlen(envp[0]);
//	char *tmp;
	char *cmd;
	int j = -1;
	while (envp[++j])
	{
		printf("envp ===== %s\n", envp[j]);
	}

	if (ac != 5)
	{
		printf("wrong number of arguments\n");
		return (-1);
	}
	path_from_envp = ft_substr(*envp, 1, len); //a completer ; substr n'est peut etre pas la meilleure fct pour aller choper le path. A mediter
		printf("envp = %s\n", path_from_envp);
	mypaths = ft_split(path_from_envp, ':'); // as for splitting the envp path, print out the result of your split and have a look. Add / at the end for the path to work correctly

	int i = 0;
	while (mypaths[i])
	{
		printf("mypath = %s\n", mypaths[i]);
		i++;
	}
	i = -1;
	while (mypaths[++i]) //adding '/' at the end of the path for it to work correctly
	{
		mypaths[i] = ft_join(mypaths[i], "/");
	}
	i = -1;
	while (mypaths[++i])
	{
		printf("mypath correct path = %s\n", mypaths[i]);
	}



	/*
	i = 2;
	tmp = av[1];
	while (av[i]) //PROBABLY USELESS
	{
		tmp = ft_strjoin(tmp, av[i]); //ATTENTION si des ' " ' etc sont inclues dans les arguments
		i++;
	}
	printf("tmp = %s\n", tmp);
	*/
	//IMO better to join all av[1] to av[5] with a space in between each -- ERRATUM no bc arg ls -la is one signe argument then the split will make it two arguments
	

	mycmdargs = ft_split(av[2], ' '); //split bugged if no entry given
	
	printf("av[0] = %s\n", av[0]);
	printf("av[1] = %s\n", av[1]);
	printf("av[2] = %s\n", av[2]);
	printf("av[3] = %s\n", av[3]);
	printf("av[4] = %s\n", av[4]);
	i = 0;
	while (mycmdargs[i])
	{
		printf("mycmdargs[%d] = %s\n", i, mycmdargs[i]);
		i++;
	}
//	pipex(envp, mycmdargs, mypaths);

	i = -1;
	while (mypaths[++i])
	{
		cmd = ft_join(mypaths[i], av[2]); //protect ft_join  ---- only assigns the last mypaths[i] to ftg, we need all paths
	execve(cmd, mycmdargs, envp);
	free(cmd);
	}
	
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
