/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:44:28 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:44:38 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str, char **envir)
{
	int		i;
	char	*temp;

	i = 0;
	while (envir[i])
	{
		temp = ft_strjoin(str, "=");
		if (ft_strncmp(temp, envir[i], ft_strlen(str) + 1) == 0)
		{
			free(temp);
			return (envir[i] + ft_strlen(str) + 1);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

int	pipe_argument(char *str)
{
	int		i;
	bool	quote;

	i = 0;
	quote = false;
	while (str[i])
	{
		if (is_quote(str[i]))
			quote = !quote;
		if (str[i] == '|' && quote == true)
			return (1);
		i++;
	}
	return (0);
}

void	fix_pipe(t_cmds *cmds, t_mshell *mshell)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < mshell->n_cmds)
	{
		j = 0;
		while (cmds[i].words[j])
		{
			if (pipe_argument(cmds[i].words[j]))
			{
				temp = ft_strtrim(cmds[i].words[j], "\"\'");
				free(cmds[i].words[j]);
				cmds[i].words[j] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
}
