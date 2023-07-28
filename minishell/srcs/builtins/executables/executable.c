/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 17:47:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **pwd)
{
	int		i;

	i = 0;
	if (!pwd)
		return (NULL);
	while (pwd[i])
	{
		if (!ft_strncmp(pwd[i], "PATH=", 5))
			return (ft_substr(pwd[i], 5, ft_strlen(pwd[i]) - 5));
		i++;
	}
	return (NULL);
}

char	**available_path(t_mshell *mshell)
{
	char	**available;
	char	*path;

	path = get_path(mshell->envior);
	available = ft_split(path, ':');
	free(path);
	return (available);
}

char	*returnvalue_aux(char **available, char *temp)
{
	int		i;
	char	*fin;
	char	*str;

	i = 0;
	if (check_temp(temp, available) == -1)
		return (NULL);
	while (available[i])
	{
		str = ft_strjoin(available[i], "/");
		free(available[i]);
		fin = ft_strjoin(str, temp);
		free(str);
		if (!access(fin, X_OK))
		{
			free_available(available, i);
			free(temp);
			return (fin);
		}
		free(fin);
		i++;
	}
	free(available);
	free(temp);
	return (NULL);
}

char	*returnvalue(char **cmd, t_mshell *mshell)
{
	char	**available;
	char	*temp;
	char	*fin;

	temp = ft_strtrim(cmd[0], " \t");
	available = available_path(mshell);
	if (free_mem(available, temp) == -1)
	{
		if (!access(cmd[0], X_OK))
			return (cmd[0]);
		else
			return (NULL);
	}
	if (check_access(temp, available) == 0)
		return (temp);
	else
	{
		if (return_aux(temp, available) == -1)
			return (temp);
		fin = returnvalue_aux(available, temp);
		if (fin != NULL)
			return (fin);
	}
	return (NULL);
}

void	executables(char **cmd, t_mshell *mshell)
{
	char	*bin;
	char	*temp;

	bin = returnvalue(cmd, mshell);
	if (bin == NULL)
		return ;
	if (cmd[1] && find_char(cmd[1], '-') != -1)
	{
		temp = ft_strtrim(cmd[1], " \t");
		free(cmd[1]);
		cmd[1] = ft_strdup(temp);
		free(temp);
	}
	execve(bin, cmd, mshell->envior);
	free(bin);
}
