/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:11:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:27:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*t;

	if (!dest && !src)
		return (EXIT_SUCCESS);
	p = dest;
	t = src;
	while (n--)
	{
		*p = *t;
		p++;
		t++;
	}
	return (dest);
}
