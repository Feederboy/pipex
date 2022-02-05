/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:56:20 by matt              #+#    #+#             */
/*   Updated: 2022/02/05 19:02:59 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_join(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
void	*get_path(char *envp[], char **mycmdargs);
char	**get_args(char **av);
int		main(int ac, char **av, char **envp);
char	**parsing_front_spaces(char **av);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char **mycmdargs, int fd);
void	ft_free_double_tab(char **str);
void	ft_cmd_err(char **mycmdargs);
void	while_instruc(char **mypaths, char *paths,
			char **mycmdargs, char **envp);
void	close_and_wait(int fd[2], int status,
			pid_t child1, pid_t child2);
#endif
