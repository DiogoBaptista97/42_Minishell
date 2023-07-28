/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:34 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:32:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bad_fd_error(t_cmds *cmds, char *str, int fd)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (cmds->fork == 1)
			exit(1);
		return (-1);
	}
	return (0);
}

void	token_more(t_cmds *cmds, int mode)
{
	int	fd;

	if (mode == 1)
	{
		if (access(cmds->redout, F_OK) == 0)
			fd = open(cmds->redout, O_RDWR | O_APPEND, 0644);
		else
			fd = open(cmds->redout, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
		fd = open(cmds->redout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_pipes(int num, int **pipefd, t_mshell *mshell, t_cmds *cmds)
{
	if (num == 0)
	{
		dup2(pipefd[num][WRITE], STDOUT_FILENO);
		close(pipefd[num][READ]);
		close(pipefd[num][WRITE]);
	}
	else if (num == mshell->n_cmds - 1)
	{
		if (cmds->redin == NULL)
			dup2(pipefd[num - 1][READ], STDIN_FILENO);
		close(pipefd[num - 1][READ]);
		close(pipefd[num - 1][WRITE]);
	}
	else
	{
		if (cmds->redin == NULL)
			dup2(pipefd[num - 1][READ], STDIN_FILENO);
		dup2(pipefd[num][WRITE], STDOUT_FILENO);
		close(pipefd[num - 1][READ]);
		close(pipefd[num - 1][WRITE]);
		close(pipefd[num][READ]);
		close(pipefd[num][WRITE]);
	}
}

void	reset_fds(t_mshell *mshell)
{
	dup2(mshell->res_pipes[READ], STDIN_FILENO);
	dup2(mshell->res_pipes[WRITE], STDOUT_FILENO);
}
