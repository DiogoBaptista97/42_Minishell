/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nalloc_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:48:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/11 20:11:16 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_check(char *str, int *count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			(*count)++;
			i++;
			while (str[i] && !is_space(str[i]) && !is_special_char(str[i])
				&& !is_quote(str[i]) && str[i] != '$')
				i++;
		}
		else
			i++;
	}
	if ((*count) != 0)
		(*count)--;
	return ;
}

void	init_dollar(char *str, int *j, char **words)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (is_space(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			i++;
			while (str[i] && !is_space(str[i]) && !is_special_char(str[i])
				&& !is_quote(str[i]) && str[i] != '$')
				i++;
			words[*j] = ft_substr(str, start, i - start);
			(*j)++;
		}
		else
			i++;
	}
	return ;
}
