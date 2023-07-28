/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:29:47 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/27 16:31:42 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	order_array(char **str)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	i = 0;
	j = 0;
	size = 0;
	while (str[size])
		size++;
	while (j < size - 1)
	{
		i = 0;
		while (i < size - j - 1)
		{
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				temp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

int	next_one(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

void	b_declare_aux(char *array, int j)
{
	char	*str;

	str = ft_substr(array, j, next_one(array, '='));
	if (find_char(array, '=') == -1)
		ft_printf("declare -x %s\n", array);
	else
		ft_printf("declare -x %s=", str);
	free(str);
}

int	b_declare(t_mshell *mshell)
{
	int		i;
	char	**array;
	char	*str;
	int		j;

	array = arraydup(mshell->envior);
	order_array(array);
	i = 0;
	while (array[i])
	{
		j = 0;
		b_declare_aux(array[i], j);
		j = j + next_one(array[i], '=') + 1;
		str = ft_substr(array[i], j, ft_strlen(array[i]));
		if (find_char(array[i], '=') != -1)
			ft_printf("\"%s\"\n", str);
		free(array[i]);
		free(str);
		i++;
	}
	free(array);
	return (EXIT_SUCCESS);
}

void	check_ex(char **n_var, int i)
{
	char	*temp;

	if (*(n_var[i] + find_char(n_var[i], '=') + 1) <= 31)
	{
		temp = ft_substr(n_var[i], 0, find_char(n_var[i], '=') + 1);
		free(n_var[i]);
		n_var[i] = ft_strdup(temp);
		free(temp);
	}
}
