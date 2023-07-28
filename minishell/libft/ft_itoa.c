/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <dbraga-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:47:31 by dbraga-b          #+#    #+#             */
/*   Updated: 2022/11/18 18:27:46 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

int	osizeitoa(int n)
{
	int	l;

	l = 0;
	if (n == 0)
		l = 1;
	if (n < 0)
		l = l + 1;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		i;

	len = osizeitoa(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	len--;
	i = 1;
	if (n < 0)
	{
		str[0] = '-';
		i = -1;
	}
	else if (n == 0)
		str[len] = '0';
	while (n != 0)
	{
		str[len] = ((n % 10) * i) + 48;
		n = n / 10;
		len--;
	}
	return (str);
}
