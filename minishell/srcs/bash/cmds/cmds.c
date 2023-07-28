/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:44 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	count_cmds(t_lexer *lexer)
{
	int		count;
	t_lexer	*temp;

	temp = lexer;
	count = 1;
	while (temp)
	{
		if (temp->word[0] == '|' && temp->next != NULL)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	check_validcmd(t_cmds cmds)
{
	if (cmds.redin == NULL && cmds.redout == NULL)
		return (0);
	if (cmds.redin && (cmds.redin[0] == '|'
			|| cmds.redin[0] == '<' || cmds.redin[0] == '>'))
	{
		g_exit_status = 2;
		ft_printf("syntax error near unexpected token \n");
		return (1);
	}
	if (cmds.redout && (cmds.redout[0] == '|'
			|| cmds.redout[0] == '<' || cmds.redout[0] == '>'))
	{
		g_exit_status = 2;
		ft_printf("syntax error near unexpected token \n");
		return (1);
	}
	return (0);
}

void	set_init(t_cmds *cmds, int i, int n)
{
	cmds[i].id = i;
	cmds[i].built = &builtins;
	cmds[i].all_words = 0;
	cmds[i].fork = 0;
	if (i == 0)
		cmds[i].prev = NULL;
	else
		cmds[i].prev = &cmds[i - 1];
	if (i == n - 1)
		cmds[i].next = NULL;
	else
		cmds[i].next = &cmds[i + 1];
}

int	alloc_cmds(t_cmds *cmds, int n, t_lexer *lexer)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	if (only_redir(lexer) == 1)
		return (2);
	while (++i < n)
	{
		set_init(cmds, i, n);
		cmds[i].words = alloc_words(&lexer[start], &cmds[i]);
		if (cmds[i].words == NULL)
			return (-1);
		if (check_validcmd(cmds[i]))
		{
			free(lexer);
			return (-1);
		}
		start += cmds[i].all_words + 1;
	}
	free(lexer);
	return (0);
}

t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell)
{
	t_cmds	*cmds;
	int		status;
	int		n;

	n = count_cmds(lexer);
	mshell->n_cmds = n;
	mshell->current_cmd = -1;
	cmds = malloc(sizeof(t_cmds) * n);
	status = alloc_cmds(cmds, n, lexer);
	if (status == -1)
	{
		free(cmds);
		return (NULL);
	}
	else if (status == 2)
	{
		cmds[0].id = 1337;
		return (cmds);
	}
	return (cmds);
}
