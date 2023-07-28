/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:30:32 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:30:44 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_cd_aux(t_mshell *mshell, char *new_dir, char *ret, char *direct)
{
	int		error;
	char	*temp;
	char	str[256];

	error = chdir((const char *)new_dir);
	ret = get_env("PWD", mshell->envior);
	if (ret == NULL)
	{
		free(new_dir);
		return (1);
	}
	temp = ft_strjoin("OLDPWD=", ret);
	b_export_one(temp, mshell);
	free(temp);
	getcwd(str, sizeof(str));
	temp = ft_strjoin("PWD=", str);
	b_export_one(temp, mshell);
	free(temp);
	if (error != 0)
		return (error_cd(new_dir));
	free(new_dir);
	if (direct == NULL)
		free (direct);
	return (EXIT_SUCCESS);
}

int	b_cd(char *direct, t_mshell *mshell)
{
	char	*ret;
	char	*new_dir;

	ret = NULL;
	if (direct == NULL || !ft_strncmp(direct, "~", 2))
	{
		ret = get_env("HOME", mshell->envior);
		if (ret == NULL)
			return (1);
		new_dir = ft_strdup(ret);
	}
	else if (!ft_strncmp(direct, "-", 2))
	{
		ret = get_env("OLDPWD", mshell->envior);
		if (ret == NULL)
			return (1);
		new_dir = ft_strdup(ret);
	}
	else
		new_dir = ft_strdup(direct);
	if (b_cd_aux(mshell, new_dir, ret, direct))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
