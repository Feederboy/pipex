/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:36:18 by matt              #+#    #+#             */
/*   Updated: 2021/12/23 18:37:14 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	int i;

	len = 0;
	i = 0;
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
