/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 15:10:34 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	check_commands(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

void	parser(t_cmds *cmds, t_mshell *mshell)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (mshell->n_cmds > 1)
		multiple_cmds(mshell, cmds);
	else
	{
		if (is_builtins(cmds->words[0]))
			g_exit_status = cmds->built(cmds, mshell);
		else
		{
			cmds[0].fork = 1;
			sig_fork(cmds[0]);
			pid = fork();
			if (pid == 0)
				cmds[0].built(&cmds[0], mshell);
			else
				waitpid(pid, &status, 0);
			if (g_exit_status != 130 && g_exit_status != 131)
				g_exit_status = WEXITSTATUS(status);
		}
		mshell->current_cmd++;
	}
	reset_signals();
}
