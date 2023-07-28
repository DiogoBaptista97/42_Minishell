/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:35:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 17:39:51 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;
	int		n;

	i = ft_strlen(s);
	ptr = malloc(sizeof(char) * (i + 1));
	n = 0;
	if (!ptr)
		return (NULL);
	while (n < i)
	{
		ptr[n] = s[n];
		n++;
	}
	ptr[n] = 0;
	return (ptr);
}
