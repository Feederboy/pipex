/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:36:18 by matt              #+#    #+#             */
/*   Updated: 2022/02/05 18:46:22 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *str, char c)
{
	int	words;
	int	count;
	int	i;

	i = 0;
	words = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (count > 0)
				words++;
			count = 0;
		}
		else
			count++;
		i++;
	}
	if (count > 0)
		words++;
	return (words);
}

static int	filltab(char **result, char const *str, char c, int pos)
{
	int	j;
	int	i;
	int	size;

	while (str[pos] && str[pos] == c)
		pos++;
	j = pos;
	while (str[j] && str[j] != c)
		j++;
	size = j;
	*result = malloc((size + 1) * sizeof(char));
	if (!(*result))
		return (-1);
	i = 0;
	while (i < size && str[pos] != c)
		(*result)[i++] = str[pos++];
	(*result)[i] = '\0';
	return (j);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;
	int		i;
	int		start;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	result = malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[size] = 0;
	i = 0;
	start = 0;
	while (i < size)
	{
		start = filltab(&result[i++], s, c, start);
		if (start == -1)
		{
			free_tab(result);
			return (NULL);
		}
	}
	return (result);
}
