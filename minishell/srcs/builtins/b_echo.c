/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:29:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 15:47:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo_aux(int i, char **words, int max_words)
{
	int		mode;

	mode = 0;
	if (i > 0)
		mode = 1;
	while (words[i])
	{
		if (i == max_words - 1)
		{
			if (mode == 0)
				printf("%s\n", words[i]);
			else
				printf("%s", words[i]);
		}
		else
			printf("%s ", words[i]);
		i++;
	}
}

int	b_echo(char **words, int max_words)
{
	int	i;
	int	j;

	if (!words[0])
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (words[i])
	{
		if (!ft_strncmp(words[i], "-n", 2))
		{
			j = 2;
			while (words[i][j] == 'n')
				j++;
			if (words[i][j] != '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	b_echo_aux(i, words, max_words);
	return (EXIT_SUCCESS);
}
