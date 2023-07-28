/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nsize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:07:58 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/05 20:54:46 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char	*name;
	char	*value;
	bool	sing;
	int		i;
	int		count;
}	t_env;

static void	handle_expand(char *str, t_mshell *mshell, t_env *env)
{
	size_t	j;

	if (str[env->i] == '$' && env->sing == false && str[env->i + 1]
		&& (ft_isalnum(str[env->i + 1]) || str[env->i + 1] == '?'))
	{
		env->name = get_name(str + env->i);
		env->count += ft_strlen(get_env(env->name, mshell->envior));
		env->i++;
		j = 0;
		while (j < ft_strlen(env->name))
		{
			j++;
			env->i++;
		}
		free(env->name);
	}
	else
	{
		env->count++;
		env->i++;
	}
}

static void	handle_db(t_env *env, char *str, t_mshell *mshell)
{
	env->i++;
	while (str[env->i] != '\"' && str[env->i] != 0)
		handle_expand(str, mshell, env);
	if (str[env->i] == '\"')
		env->i++;
}

int	get_nsize(char *str, t_mshell *mshell)
{
	t_env	env;

	env.i = 0;
	env.count = 0;
	env.sing = false;
	while (str[env.i])
	{
		if (str[env.i] == '\'')
		{
			env.sing = !env.sing;
			env.i++;
			continue ;
		}
		if (str[env.i] == '\"' && env.sing == false)
			handle_db(&env, str, mshell);
		else
			handle_expand(str, mshell, &env);
	}
	return (env.count);
}
