/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:56:20 by matt              #+#    #+#             */
/*   Updated: 2021/12/23 18:47:09 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_split(const char *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
int		main(int ac, char **av, char **envp);

#endif
