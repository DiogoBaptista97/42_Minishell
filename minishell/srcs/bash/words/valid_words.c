/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:57:18 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/07/27 16:20:28 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_redir(char *words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i])
	{
		if (words[i] == '>' || words[i] == '<')
			count++;
		i++;
	}
	if (count > 2)
		return (1);
	return (0);
}

int	valid_words(char **words)
{
	int	i;

	if (words[0] == NULL || words[0][0] == '|')
		return (0);
	if (words[0][0] == '<' && words[0][1] == '\0')
		return (0);
	i = -1;
	while (words[++i])
	{
		if (is_quote(words[i][0]))
			continue ;
		if (words[i][0] == ';')
			return (0);
		else if (words[i][0] == '&' || words[i][0] == '(')
			return (0);
		else if (words[i][ft_strlen(words[i]) - 1] == ')')
			return (0);
		else if (ft_strncmp(words[i], "||", 3) == 0 || multiple_redir(words[i]))
			return (0);
		else if (ft_strncmp(words[i], "><", 3) == 0)
			return (0);
		else if (is_redir(words[i]) && words[i + 1] == NULL)
			return (0);
	}
	return (1);
}

int	valid_nvar(char *nvar)
{
	int	j;

	if (nvar[0] == '?')
		return (EXIT_SUCCESS);
	if (!ft_isalpha(nvar[0]) && nvar[0] != '_')
		return (EXIT_FAILURE);
	j = 1;
	while (nvar[j] != '=' && nvar[j] != '\0')
	{
		if (!(ft_isalnum(nvar[j])))
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	valid_nvar_one(char *nvar)
{
	int	i;

	if (nvar[0] == '?')
		return (EXIT_SUCCESS);
	if (!ft_isalpha(nvar[0]) || nvar[0] == '_')
		return (EXIT_FAILURE);
	i = 1;
	while (nvar[i] != '=' && nvar[i] != '\0')
	{
		if (!ft_isalnum(nvar[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
