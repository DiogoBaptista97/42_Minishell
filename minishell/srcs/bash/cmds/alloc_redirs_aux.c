/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redirs_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:57:30 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/13 16:42:42 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	condit_redir(t_lexer *lexer)
{
	if (lexer && lexer->word[0] == '|')
		free(lexer->word);
}

int	attr_redir_in_aux(t_cmds *cmds, t_lexer *aux)
{
	char	*temp;

	if (cmds->next == NULL && !valid_redir(aux->word)
		&& ft_strncmp(cmds->tokenin, "<<", 2) != 0)
	{
		free(cmds->tokenin);
		if (cmds->redin != NULL)
			free(cmds->redin);
		return (-1);
	}
	if (cmds->redin != NULL)
		free(cmds->redin);
	if (ft_strncmp(aux->word, ">", 2) == 0)
		return (0);
	cmds->redin = ft_strdup(aux->word);
	if (ft_strncmp(cmds->tokenin, "<<", 2) == 0)
	{
		temp = remove_quotes(cmds->redin);
		cr_heredoc(cmds->id, temp);
		free(temp);
	}
	return (0);
}

int	attr_redir_in(t_cmds *cmds, t_lexer *lexer)
{
	t_lexer	*aux;

	if (cmds->tokenin != NULL)
		free(cmds->tokenin);
	cmds->tokenin = ft_strdup(lexer->word);
	aux = lexer->next;
	if (aux == NULL)
	{
		free(cmds->tokenin);
		return (-2);
	}
	if (attr_redir_in_aux(cmds, aux) == -1)
		return (-1);
	return (0);
}

int	check_status(int status)
{
	if (status == -1)
	{
		g_exit_status = 1;
		return (-1);
	}
	else if (status == -2)
	{
		g_exit_status = 2;
		return (-1);
	}
	return (0);
}
