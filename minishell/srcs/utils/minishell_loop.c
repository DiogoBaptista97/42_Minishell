/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:36:40 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 18:12:36 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*chamada(void)
{
	char	*str;
	char	buff[256];

	str = getcwd(buff, sizeof(buff));
	str = ft_strjoin(str, "$ ");
	return (str);
}

char	*prompt_read(t_mshell *mshell)
{
	char	*prompt;
	char	*line;

	prompt = chamada();
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
	{
		free(line);
		write (1, "exit\n", 5);
		b_exit(1, mshell);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

void	minishell_loopit(char **words, t_mshell *mshell)
{
	t_cmds		*cmds;
	t_lexer		*lexer;
	size_t		count;

	count = count_words(words);
	lexer = init_lexer(words, count, mshell);
	cmds = init_cmds(lexer, mshell);
	if (cmds == NULL)
	{
		free(lexer);
		b_export_one("?=1", mshell);
		write(2, "minishell: No such file or directory\n", 37);
		return ;
	}
	else if (cmds[0].id == 1337)
	{
		free(lexer);
		free(cmds);
		return ;
	}
	fix_redir(cmds, mshell);
	fix_pipe(cmds, mshell);
	parser(cmds, mshell);
	change_exit_st(mshell);
	clear_mem(mshell, cmds);
}

char	**start_loop(t_mshell *mshell)
{
	char		*prompt;
	char		**words;

	prompt = prompt_read(mshell);
	if (g_exit_status == 130)
		change_exit_st(mshell);
	words = init_words(prompt);
	if (words == NULL)
	{
		free(prompt);
		return (NULL);
	}
	free(prompt);
	return (words);
}

void	minishell_loop(t_mshell *mshell)
{
	char	**words;

	while (1)
	{
		g_exit_status = 0;
		mshell->res_pipes[READ] = dup(STDIN_FILENO);
		mshell->res_pipes[WRITE] = dup(STDOUT_FILENO);
		words = start_loop(mshell);
		if (words == NULL)
			continue ;
		if (!(words[0] == NULL))
		{
			if (valid_words(words))
				minishell_loopit(words, mshell);
			else
			{
				free_array(words);
				ft_printf("minishell: syntax error\n");
				b_export_one("?=2", mshell);
			}
		}
		reset_fds(mshell);
	}
}
