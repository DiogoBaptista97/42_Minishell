/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:27:36 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/05 20:27:53 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	char			*t1;
	char			*t2;

	t1 = (char *)s1;
	t2 = (char *)s2;
	while (*t1 && *t2 && (*t1 == *t2))
	{
		t1++;
		t2++;
	}
	return ((int)(unsigned char)(*t1) - (int)(unsigned char)(*t2));
}
