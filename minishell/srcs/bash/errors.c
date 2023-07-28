/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:13:36 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/06/14 16:30:40 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cmd_not_found(t_cmds *cmds)
{
	ft_putstr_fd("Command '", STDERR_FILENO);
	ft_putstr_fd(cmds->words[0], STDERR_FILENO);
	ft_putstr_fd("' not found\n", STDERR_FILENO);
	if (cmds->words[0][0] == 0)
		exit(0);
	else if (valid_redir(cmds->words[0]))
		exit(126);
	exit (127);
}

int	error_cd(char *cmd)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	free(cmd);
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	error_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
