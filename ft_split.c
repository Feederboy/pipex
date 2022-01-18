/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:36:18 by matt              #+#    #+#             */
/*   Updated: 2022/01/18 16:35:44 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
static int		count_words(char const *str, char c)
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

static int		filltab(char **result, char const *str, char c, int pos)
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

static void		free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char			**ft_split(char const *s, char c)
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

*/


/*

static int		ft_taille_word(const char *s, char c)
{
	int len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static int		ft_sepe(char curr, char c)
{
	return (curr == c);
}

static int		ft_nbwords(const char *s, char c)
{
	int len;

	len = 0;
	while (*s)
	{
		if (ft_sepe(*s, c))
			s++;
		else
		{
			while (*s && !ft_sepe(*s, c))
				s++;
			len++;
		}
	}
	return (len);
}

static char		**ft_free(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	return (res);
}

char			**ft_split(const char *s, char c)
{
	char	**res;
	int		i;
	int		nb_words;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_nbwords(s, c);
	res = malloc(sizeof(char *) * (nb_words + 1));
	if (!res)
		return (NULL);
	while (nb_words-- > 0)
	{
		while (*s && *s == c)
			s++;
		len = ft_taille_word(s, c);
		res[i] = ft_substr(s, 0, len);
		if (!res[i])
			return (ft_free(res, i));
		s = s + len;
		i++;
	}
	res[i] = NULL;
	return (res);
}
*/


static	int	ft_issep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static	int	ft_count_words(char const *s, char c)
{
	int		i;
	int		words;
	int		count;

	i = 0;
	words = 0;
	count = 0;
	while (s[i])
	{
		if (ft_issep(s[i], c) == 1)
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

static	int	ft_fill(char **dst, char const *s, char c, int index)
{
	int		size;
	int		i;
	int		pos;

	while (s[index] && ft_issep(s[index], c))
	{
		index++;
	}
	pos = index;
	size = 0;
	while (s[pos] && !ft_issep(s[pos], c))
	{
		pos++;
		size++;
	}
	*dst = malloc(sizeof(char) * (size + 1));
	if (!(*dst))
		return (0);
	i = 0;
	while (i < size && !(ft_issep(s[index], c)))
	{
		(*dst)[i++] = s[index++];
	}
	(*dst)[i] = '\0';
	return (pos);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		size;
	int		i;
	int		index;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	dst = malloc(sizeof(char *) * (size + 1));
	if (!(dst))
		return (NULL);
	dst[size] = 0;
	i = 0;
	index = 0;
	while (i < size)
	{
		index = ft_fill(&dst[i++], s, c, index);
	}
	return (dst);
}
