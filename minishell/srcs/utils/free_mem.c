/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:39:42 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 22:13:18 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_mem(char **available, char *temp)
{
	if (available == NULL)
	{
		free(temp);
		return (-1);
	}
	return (0);
}

void	free_redout(t_cmds *cmds)
{
	if (cmds->redout)
	{
		free(cmds->redout);
		free(cmds->tokenout);
	}
}

void	free_available(char **available, int i)
{
	while (available[i + 1])
		free(available[++i]);
	free(available);
}

int	check_temp(char *temp, char **available)
{
	int	i;

	i = -1;
	if (temp[0] == 0)
	{
		free_available(available, i);
		free(temp);
		return (-1);
	}
	return (0);
}
