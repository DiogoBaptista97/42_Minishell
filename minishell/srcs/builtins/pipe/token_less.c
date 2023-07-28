/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:59:23 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 18:33:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	token_less(t_cmds *cmds, int mode)
{
	int			fd;
	char		*temp;
	char		*name;

	temp = ft_itoa(cmds->id);
	name = ft_strjoin("heredoc", temp);
	free(temp);
	if (mode == 0)
	{
		fd = open(cmds->redin, O_RDONLY);
		if (bad_fd_error(cmds, cmds->redin, fd) == -1)
		{
			free(name);
			return (-1);
		}
	}
	else
		fd = open(name, O_RDONLY);
	free(name);
	dup_fd(fd);
	return (0);
}
