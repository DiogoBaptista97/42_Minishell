/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:22:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:05:58 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

size_t	count_words(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

void	change_exit_st(t_mshell *mshell)
{
	char	*status;
	char	*str;

	status = ft_itoa(g_exit_status);
	str = ft_strjoin("?=", status);
	b_export_one(str, mshell);
	free(status);
	free(str);
}

int	find_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (i == ft_strlen(str) && c != 0)
		return (-1);
	else
		return (i);
}

int	is_redir(char *str)
{
	if (!ft_strncmp(str, ">>", 2) && ft_strlen(str) == 2)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(str, "<<", 2) && ft_strlen(str) == 2)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(str, ">", 1) && ft_strlen(str) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_builtins(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (EXIT_FAILURE);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (EXIT_FAILURE);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (EXIT_FAILURE);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (EXIT_FAILURE);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (EXIT_FAILURE);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (EXIT_FAILURE);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
