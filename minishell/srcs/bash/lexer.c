/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:55:39 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 18:08:32 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_lexer(t_lexer *lexer, char **words, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		lexer[i].word = ft_strdup(words[i]);
		free(words[i]);
		if (lexer[i].word == NULL)
			lexer[i].word = " ";
		if (i != 0)
			lexer[i].prev = &lexer[i - 1];
		else
			lexer[i].prev = NULL;
		if (i != n - 1)
			lexer[i].next = &lexer[i + 1];
		else
			lexer[i].next = NULL;
		i++;
	}
	free(words);
}

void	clear_dollar_aux(t_lexer *lexer, int i)
{
	char	*ret;

	if (ft_isdigit(lexer->word[i + 1]) == 1
		&& lexer->word[i + 2] != '\0')
		ret = ft_substr(lexer->word, i + 2, ft_strlen(lexer->word) - i - 2);
	else
		ret = ft_strtrim(lexer->word, "$");
	free(lexer->word);
	lexer->word = ft_strdup(ret);
	free(ret);
}

void	clear_dollar(t_lexer *lexer)
{
	int		i;
	bool	sing_quote;

	i = 0;
	sing_quote = false;
	while (lexer->word[i])
	{
		if (lexer->word[i] == '\'')
			sing_quote = !sing_quote;
		else if (lexer->word[i] == '$' && sing_quote == false
			&& lexer->word[i + 1] != '\0'
			&& ft_isalpha(lexer->word[i + 1]) == 0
			&& lexer->word[i + 1] != '?' && lexer->word[i + 1] != '$')
		{
			clear_dollar_aux(lexer, i);
			break ;
		}
		i++;
	}
}

void	expand_lexer(t_lexer *lexer, t_mshell *mshell, int n)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < n)
	{
		clear_dollar(&lexer[i]);
		if (i == 0)
			str = expand_env(lexer[i].word, mshell);
		else if (!is_redir(lexer[i - 1].word) && !pipe_argument(lexer[i].word))
			str = expand_env(lexer[i].word, mshell);
		else
			str = ft_strdup(lexer[i].word);
		free(lexer[i].word);
		lexer[i].word = ft_strdup(str);
		free(str);
	}
}

t_lexer	*init_lexer(char **words, int n, t_mshell *mshell)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer) * n);
	create_lexer(lexer, words, n);
	expand_lexer(lexer, mshell, n);
	return (lexer);
}
