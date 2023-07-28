/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:16:29 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 20:06:13 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	clear_cmds(t_cmds *cmds, int n_cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_cmds)
	{
		j = 0;
		while (cmds[i].words[j])
		{
			free(cmds[i].words[j]);
			j++;
		}
		free(cmds[i].words);
		if (cmds[i].redin)
			free(cmds[i].redin);
		if (cmds[i].tokenin)
			free(cmds[i].tokenin);
		if (cmds[i].redout)
		{
			free(cmds[i].redout);
			free(cmds[i].tokenout);
		}
		i++;
	}
	free(cmds);
}

void	free_envior(t_mshell *mshell)
{
	int	i;

	i = -1;
	while (mshell->envior[++i])
		free(mshell->envior[i]);
	free(mshell->envior[i]);
	free(mshell->envior);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp;

	temp = lexer;
	while (temp)
	{
		free(temp->word);
		temp = temp->next;
	}
}

void	clear_mem(t_mshell *mshell, t_cmds *cmds)
{
	int		i;
	char	*num;
	char	*temp;

	clear_cmds(cmds, mshell->n_cmds);
	i = 0;
	while (i < mshell->n_cmds)
	{
		num = ft_itoa(i);
		temp = ft_strjoin("heredoc", num);
		free(num);
		unlink(temp);
		free(temp);
		i++;
	}
}
