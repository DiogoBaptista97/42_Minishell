/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:02:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:51 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_words_quotes(char *str, int *i, int *j, char **words)
{
	int		start;
	char	quote;

	start = *i;
	quote = str[*i];
	while (str[*i] && is_space(str[*i]) != 1)
	{
		(*i)++;
		while (str[*i] && str[*i] != quote)
			(*i)++;
		(*i)++;
		if (is_quote(str[*i]))
		{
			quote = str[*i];
			continue ;
		}
		else if (init_w_quote_aux(str, i, &quote) == 0)
			continue ;
	}
	words[*j] = ft_substr(str, start, *i - start);
	(*j)++;
}

void	init_words_special_chars(char *str, int *i, int *j, char **words)
{
	int		start;
	char	c;

	start = *i;
	c = str[*i];
	while (str[*i] == c)
		(*i)++;
	words[*j] = ft_substr(str, start, *i - start);
	(*i)--;
	(*j)++;
}

void	init_words_word(char *str, int *i, int *j, char **words)
{
	int		start;
	char	c;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '|')
	{
		if (is_quote(str[*i]))
		{
			c = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != c)
				(*i)++;
		}
		(*i)++;
	}
	words[*j] = ft_substr(str, start, *i - start);
	if (str[*i] && (str[*i] == '<' || str[*i] == '>' || str[*i] == '|'))
		(*i)--;
	(*j)++;
}

void	init_words_loop(char *str, char **words, int count)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (find_char(str, ' ') == -1)
		init_dollar(str, &j, words);
	while (j < count)
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			init_words_quotes(str, &i, &j, words);
		else if (is_special_char(str[i]))
			init_words_special_chars(str, &i, &j, words);
		else
			init_words_word(str, &i, &j, words);
		i++;
	}
	words[j] = NULL;
}

char	**init_words(char	*str)
{
	int		count;
	char	**words;

	if (str[0] == '\0')
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (NULL);
	count = nalloc_words(str);
	if (count == -1)
	{
		ft_printf("minishell: syntax error unclosed\n");
		return (NULL);
	}
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	init_words_loop(str, words, count);
	if (check_pipe(words, count) == 0)
		return (NULL);
	return (words);
}
