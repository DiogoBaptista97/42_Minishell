/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:47:03 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 12:20:25 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		flag;
	int		start;
}	t_vars;

int	ft_get_size(char *str, char *substr, char *replace)
{
	return (ft_strlen(str) - ft_strlen(substr) + ft_strlen(replace));
}

t_vars	init_vars(void)
{
	t_vars	vars;

	vars.i = -1;
	vars.j = 0;
	vars.flag = 0;
	return (vars);
}

int	ft_get_start(char *str, char *substr)
{
	t_vars	vars;

	vars = init_vars();
	while (str[++vars.i])
	{
		if (str[vars.i] == substr[vars.j])
		{
			if (!vars.flag)
				vars.start = vars.i;
			vars.j++;
			if (substr[vars.j] == '\0')
				break ;
			vars.flag = 1;
		}
		else
		{
			vars.flag = 0;
			vars.start = 0;
			vars.j = 0;
		}
	}
	if (substr[vars.j] == '\0' && vars.flag)
		return (vars.start);
	else
		return (-1);
}

char	*get_done(char *output, char *str, char *replace, char *substr)
{
	int		i;
	size_t	j;
	int		start;

	i = -1;
	j = 0;
	start = ft_get_start(str, substr);
	if (start != -1)
	{
		while (++i < start)
			output[i] = str[i];
		while (j < ft_strlen(replace))
			output[i++] = replace[j++];
		j = start + ft_strlen(substr);
		while (str[j])
			output[i++] = str[j++];
		output[i] = '\0';
	}
	else
	{
		free(output);
		return (NULL);
	}
	return (output);
}

char	*ft_replace_env(char *str, char *substr, char *replace)
{
	char	*output;

	output = malloc(sizeof(char) * (ft_get_size(str, substr, replace) + 1));
	output = get_done(output, str, replace, substr);
	if (!output)
		return (NULL);
	else
		return (output);
}
