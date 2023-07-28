/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:49:25 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/07/05 20:56:58 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_double_special_char(char c1, char c2)
{
	return (c1 == c2 && (c1 == '<' || c1 == '>'));
}

void	another_quote(int *i, char *str)
{
	int	temp;

	(*i)++;
	temp = *i;
	(*i)++;
	while (str[*i] && str[*i] != str[temp])
		(*i)++;
}
