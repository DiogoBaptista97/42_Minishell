/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:38:50 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/26 17:05:10 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nalloc_words_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i] && str[i] != c)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

int	nalloc_words_space(char *str, int i, int *count)
{
	(*count)++;
	while (str[i] && is_space(str[i]))
		i++;
	return (i - 1);
}

int	nalloc_words_special_chars(char *str, int i, int *count)
{
	char	c;

	c = str[i];
	if (i > 0 && !is_space(str[i - 1]) && !is_special_char(str[i - 1]))
		(*count)++;
	(*count)++;
	i++;
	if (is_double_special_char(str[i - 1], str[i]))
		i++;
	while (str[i] && (is_space(str[i]) || str[i] == c))
		i++;
	return (i - 1);
}

int	nalloc_words_word(char *str, int i)
{
	while (str[i] && !is_space(str[i]) && !is_special_char(str[i])
		&& !is_quote(str[i]))
		i++;
	return (i - 1);
}

int	nalloc_words(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (i == 0 && count == 0 && find_char(str, ' ') == -1)
			dollar_check(str, &count);
		if (is_quote(str[i]))
			i = nalloc_words_quotes(str, i);
		else if (is_space(str[i]))
			i = nalloc_words_space(str, i, &count);
		else if (is_special_char(str[i]))
			i = nalloc_words_special_chars(str, i, &count);
		else
			i = nalloc_words_word(str, i);
		if (i == -1)
			return (-1);
		i++;
	}
	if (is_space(str[i - 1]) || is_special_char(str[i - 1]))
		return (count);
	return (count + 1);
}
