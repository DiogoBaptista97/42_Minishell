/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:25:53 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/10 20:43:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_size(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
			size++;
		i++;
	}
	return (size);
}

char	*remove_quotes(char *str)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * new_size(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
