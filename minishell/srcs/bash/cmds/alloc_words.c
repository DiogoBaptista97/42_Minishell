/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:56:32 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:04:59 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_until_cmd(t_cmds *cmds)
{
	int		i;

	free_redout(cmds);
	cmds = cmds->prev;
	while (cmds)
	{
		i = 0;
		while (cmds->words[i])
		{
			free(cmds->words[i]);
			i++;
		}
		if (cmds->words)
			free(cmds->words);
		if (cmds->redin)
			free(cmds->redin);
		if (cmds->tokenin)
			free(cmds->tokenin);
		free_redout(cmds);
		cmds = cmds->prev;
	}
}

int	get_return(t_cmds *cmds, t_lexer *lexer, char **words)
{
	int	i;

	if (find_redir(lexer, cmds) == -1)
	{
		i = 0;
		while (words[i])
		{
			free(words[i]);
			i++;
		}
		free(words);
		free_until_cmd(cmds);
		return (-1);
	}
	return (0);
}

char	**alloc_words_aux(t_lexer *lexer, t_cmds *cmds)
{
	int		j;
	char	**words;
	t_lexer	*temp;

	j = 0;
	words = malloc(sizeof(char *) * (cmds->count_words + 1));
	if (!words)
		return (NULL);
	temp = lexer;
	while (j < cmds->count_words)
	{
		if (j == 0 || !is_redir(temp->word))
		{
			words[j] = ft_strdup(temp->word);
			j++;
		}
		else
			temp = temp->next;
		temp = temp->next;
	}
	words[j] = NULL;
	if (get_return(cmds, lexer, words) == -1)
		return (NULL);
	return (words);
}

int	is_valid(t_lexer *temp)
{
	if (temp->word && (temp->word[0] == '|'
			|| temp->word[0] == '<' || temp->word[0] == '>'))
	{
		free(temp->word);
		return (-1);
	}
	return (0);
}

char	**alloc_words(t_lexer *lexer, t_cmds *cmds)
{
	char	**words;
	t_lexer	*temp;

	cmds->count_words = 0;
	temp = lexer;
	if (is_valid(temp) == -1)
		return (NULL);
	while (temp)
	{
		if (temp->word[0] == '|')
			break ;
		if (is_redir(temp->word))
		{
			temp = temp->next;
			if (temp == NULL)
				break ;
		}
		else
			cmds->count_words++;
		temp = temp->next;
	}
	words = alloc_words_aux(lexer, cmds);
	return (words);
}
