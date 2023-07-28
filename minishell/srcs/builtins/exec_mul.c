/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:59:41 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/12 18:04:21 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	exec_child(t_mshell *mshell, t_cmds *cmds, int **pipefd, int i)
{
	handle_pipes(i, pipefd, mshell, &cmds[i]);
	if (is_builtins(cmds[i].words[0]))
		g_exit_status = cmds[i].built(&cmds[i], mshell);
	else
		cmds[i].built(&cmds[i], mshell);
	exit(g_exit_status);
}

void	end_exec(t_mshell *mshell, pid_t *pid, int **pipefd)
{
	int	i;
	int	status;

	i = mshell->n_cmds - 1;
	while (i >= 0)
	{
		if (i == mshell->n_cmds -1)
			waitpid(pid[i], &status, 0);
		else
			waitpid(pid[i], NULL, 0);
		if (i != 0)
		{
			close(pipefd[i - 1][READ]);
			close(pipefd[i - 1][WRITE]);
		}
		i--;
	}
	free(pid);
	i = 0;
	while (i < mshell->n_cmds - 1)
		free(pipefd[i++]);
	free(pipefd);
	if (!WTERMSIG(status) && g_exit_status != 130 && g_exit_status != 131)
		g_exit_status = WEXITSTATUS(status);
}

void	init_pipefd(int **pipefd, t_mshell *mshell, t_cmds *cmds)
{
	int		i;

	(void) cmds;
	i = -1;
	while (++i < mshell->n_cmds - 1)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		pipe(pipefd[i]);
	}
}

void	multiple_cmds(t_mshell *mshell, t_cmds *cmds)
{
	int		**pipefd;
	pid_t	*pid;
	int		i;

	pipefd = malloc(sizeof(int *) * mshell->n_cmds);
	pid = malloc(sizeof(pid_t) * mshell->n_cmds);
	init_pipefd(pipefd, mshell, cmds);
	i = -1;
	while (++i < mshell->n_cmds)
	{
		sig_fork(cmds[i]);
		pid[i] = fork();
		if (pid[i] < 0)
			exit(EXIT_FAILURE);
		else if (pid[i] == 0)
			exec_child(mshell, cmds, pipefd, i);
		if (i < mshell->n_cmds - 1)
			close(pipefd[i][WRITE]);
		if (i > 0)
			close(pipefd[i - 1][READ]);
	}
	end_exec(mshell, pid, pipefd);
}
