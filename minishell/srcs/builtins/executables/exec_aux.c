/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:29:44 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/15 19:29:41 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *temp, char **available)
{
	if (!access(temp, X_OK))
	{
		free_available(available, -1);
		return (0);
	}
	return (1);
}

int	return_aux(char *temp, char **available)
{
	if (find_char(temp, '/') != -1)
	{
		free_available(available, -1);
		return (-1);
	}
	return (0);
}
