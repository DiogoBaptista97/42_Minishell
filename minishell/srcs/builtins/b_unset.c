/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:32:51 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/13 17:26:10 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exists(char *var, t_mshell *mshell)
{
	int	i;

	i = 0;
	if (find_char(var, '=') != -1)
		return (0);
	while (mshell->envior[i] != NULL)
	{
		if (ft_strncmp(var, mshell->envior[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	b_unset_aux(t_mshell *mshell, char **var, int i)
{
	int		count;
	int		track;
	char	**new_environ;

	count = 0;
	while (mshell->envior[count] != NULL)
		count++;
	new_environ = (char **)malloc(sizeof(char *) * count);
	count = 0;
	track = 0;
	while (mshell->envior[count] != NULL)
	{
		if (ft_strncmp(var[i], mshell->envior[count], ft_strlen(var[i])))
		{
			new_environ[track] = ft_strdup(mshell->envior[count]);
			track++;
		}
		count++;
	}
	new_environ[track] = NULL;
	free_envior(mshell);
	mshell->envior = arraydup(new_environ);
	free_array(new_environ);
}

int	b_unset(char **variable, t_mshell *mshell)
{
	int	i;
	int	mode;

	i = 1;
	mode = 0;
	while (variable[i])
	{
		if (find_char(variable[i], '=') != -1)
			mode = 1;
		if (!var_exists(variable[i], mshell))
		{
			i++;
			continue ;
		}
		else
			b_unset_aux(mshell, variable, i);
		i++;
	}
	if (mode == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
