/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:12:50 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 21:57:27 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_redir(t_lexer *lexer)
{
	t_lexer	*aux;

	if (!is_redir(lexer->word))
		return (-1);
	aux = lexer;
	while (aux)
	{
		if (is_redir(aux->word))
		{
			if (ft_strncmp(aux->word, ">", 2) == 0)
				open(aux[1].word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (ft_strncmp(aux->word, ">>", 3) == 0)
				open(aux[1].word, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (ft_strncmp(aux->word, "<<", 3) == 0)
			{
				cr_heredoc(0, aux[1].word);
				unlink("heredoc0");
			}
			free(aux->word);
			aux = aux->next;
			free(aux->word);
		}
		aux = aux->next;
	}
	return (1);
}
