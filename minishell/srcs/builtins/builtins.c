/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/06/14 17:43:56 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_exit(int status, t_mshell *mshell)
{
	int	i;

	i = -1;
	while (mshell->envior[++i])
		free(mshell->envior[i]);
	free(mshell->envior[i]);
	free(mshell->envior);
	exit(status);
}

int	b_pwd(void)
{
	char	str[256];

	getcwd(str, sizeof(str));
	if (!str[0])
		return (EXIT_FAILURE);
	printf("%s\n", str);
	return (EXIT_SUCCESS);
}

int	b_env(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->envior[i])
	{
		if (find_char(mshell->envior[i], '=') != -1)
			ft_printf("%s\n", mshell->envior[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_redirect(t_cmds *cmds)
{
	if (cmds->tokenin != NULL)
	{
		if (!ft_strncmp(cmds->tokenin, "<<", 2))
		{
			if (token_less(cmds, 1) == -1)
				return (-1);
		}
		else if (!ft_strncmp(cmds->tokenin, "<", 1))
		{
			if (token_less(cmds, 0) == -1)
				return (-1);
		}
	}
	if (cmds->tokenout != NULL)
	{
		if (!ft_strncmp(cmds->tokenout, ">>", 2))
			token_more(cmds, 1);
		else if (!ft_strncmp(cmds->tokenout, ">", 1))
			token_more(cmds, 0);
	}
	return (0);
}

int	builtins(t_cmds *cmds, t_mshell *mshell)
{
	if (check_redirect(cmds) == -1)
	{
		ft_putstr_fd("minishell: no such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 4))
			return (b_pwd());
		else if (!ft_strncmp("echo", cmds->words[0], 5))
			return (b_echo(&cmds->words[1], cmds->count_words - 1));
		else if (!ft_strncmp("cd", cmds->words[0], 3))
		{
			if (cmds->words[1] != NULL && cmds->words[2] != NULL)
				return (error_too_many_args());
			return (b_cd(cmds->words[1], mshell));
		}
		else
			return (builtins_aux(cmds, mshell));
	}
	return (error_cmd_not_found(cmds));
}
