/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:31:31 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 17:56:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int		count;
	int		mode;
}	t_vars;

t_vars	get_vars(char *n_var, t_mshell *mshell)
{
	t_vars	vars;

	vars.count = 0;
	vars.mode = 0;
	while (mshell->envior[vars.count])
	{
		if (!ft_strncmp(n_var, mshell->envior[vars.count]
				, find_char(n_var, '=')))
			vars.mode = 1;
		vars.count++;
	}
	if (vars.mode == 1)
		vars.count--;
	return (vars);
}

char	**b_export_aux(t_mshell *mshell, char *n_var, t_vars vars)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (vars.count + 2));
	while (mshell->envior[i])
	{
		if (!ft_strncmp(n_var, mshell->envior[i], find_char(n_var, '=')))
			new_env[i] = ft_strdup(n_var);
		else
			new_env[i] = ft_strdup(mshell->envior[i]);
		i++;
	}
	if (vars.mode == 0)
	{
		new_env[i] = ft_strdup(n_var);
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free_envior(mshell);
	return (new_env);
}

int	b_export(char **n_var, t_mshell *mshell)
{
	t_vars	vars;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	if (!n_var[1])
		return (b_declare(mshell));
	while (n_var[++i])
	{
		if (valid_nvar(n_var[i]))
		{
			flag = 1;
			continue ;
		}
		check_ex(n_var, i);
		vars = get_vars(n_var[i], mshell);
		mshell->envior = b_export_aux(mshell, n_var[i], vars);
	}
	return (flag);
}

int	b_export_one(char *n_var, t_mshell *mshell)
{
	t_vars	vars;
	char	*temp;

	if (find_char(n_var, '=') == -1)
		return (EXIT_SUCCESS);
	if (!n_var)
		return (b_declare(mshell));
	if (valid_nvar_one(n_var))
		return (EXIT_FAILURE);
	if (*(n_var + find_char(n_var, '=') + 1) <= 32)
	{
		temp = ft_substr(n_var, 0, find_char(n_var, '=') + 1);
		free(n_var);
		n_var = ft_strdup(temp);
		free(temp);
	}
	vars = get_vars(n_var, mshell);
	mshell->envior = b_export_aux(mshell, n_var, vars);
	return (EXIT_SUCCESS);
}
