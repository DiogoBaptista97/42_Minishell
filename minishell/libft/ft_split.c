/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <dbraga-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:34:16 by dbraga-b          #+#    #+#             */
/*   Updated: 2022/11/14 16:02:08 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	wordscount(char const *s, char c)
{
	size_t	i;
	size_t	flag;
	int		words;

	i = 0;
	flag = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			words++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (words);
}

int	next(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**makearray(char **array, int wordcount, char const *s, char c)
{
	char	*str;
	int		i;
	int		h;

	h = 0;
	i = 0;
	while (wordcount > 0)
	{
		wordcount--;
		while (s[i] == c)
			i++;
		str = ft_substr(s, i, next(&s[i], c));
		if (!str)
			return (NULL);
		array[h++] = ft_strdup(str);
		free(str);
		i = i + (next(&s[i], c));
	}
	array[h] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	char	**array;

	if (!s)
		return (NULL);
	wordcount = wordscount(s, c);
	array = malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	array = makearray(array, wordcount, s, c);
	return (array);
}
