/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:38:19 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 18:08:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READ 0
# define WRITE 1
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_lexer
{
	char			*word;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_mshell
{
	int		n_cmds;
	int		current_cmd;
	char	**envior;
	int		res_pipes[2];
	int		i;
	int		j;
}	t_mshell;

typedef struct s_cmds	t_cmds;

typedef struct s_cmds
{
	int				id;
	char			**words;
	int				fork;
	int				count_words;
	int				(*built)(t_cmds *, t_mshell *);
	char			*tokenin;
	char			*tokenout;
	char			*redin;
	char			*redout;
	int				all_words;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_panic
{
	t_cmds		*cmds;
	t_mshell	*mshell;
	t_lexer		*lexer;
}	t_panic;

//Utils
size_t	count_words(char **words);
void	change_exit_st(t_mshell *mshell);
int		find_char(char *str, char c);
int		is_redir(char *str);
int		is_builtins(char *str);
char	*ft_replace_env(char *str, char *substr, char *replace);
int		valid_nvar(char *nvar);
int		valid_nvar_one(char *nvar);
char	*remove_quotes(char *str);
//Minishell_loop
void	minishell_loop(t_mshell *mshell);
//Lexer
t_lexer	*init_lexer(char **words, int n, t_mshell *mshell);
//Cmds
t_cmds	*init_cmds(t_lexer *lexer, t_mshell *mshell);
//Heredocs
void	cr_heredoc(int id, char *redin);
//Redirs
int		find_redir(t_lexer *lexer, t_cmds *cmds);
int		only_redir(t_lexer *lexer);
void	fix_redir(t_cmds *cmds, t_mshell *mshell);
void	fix_pipe(t_cmds *cmds, t_mshell *mshell);
int		valid_redir(char *redi);
int		attr_redir_in(t_cmds *cmds, t_lexer *lexer);
int		check_status(int status);
void	condit_redir(t_lexer *lexer);
int		bad_fd_error(t_cmds *cmds, char *str, int fd);
//Parser
void	parser(t_cmds *cmds, t_mshell *mshell);
//Builtins
int		builtins_aux(t_cmds *cmds, t_mshell *mshell);
int		builtins(t_cmds *cmds, t_mshell *mshell);
void	b_exit(int status, t_mshell *mshell);
int		b_env(t_mshell *mshell);
void	order_array(char **str);
int		next_one(char *s, char c);
int		check_redirect(t_cmds *cmds);
//Exc_mul
void	multiple_cmds(t_mshell *mshell, t_cmds *cmds);
//B_unset
int		b_unset(char **variable, t_mshell *mshell);
//B_export
int		b_export(char **n_var, t_mshell *mshell);
int		b_declare(t_mshell *mshell);
int		b_export_one(char *n_var, t_mshell *mshell);
void	check_ex(char **n_var, int i);
//B_echo
int		b_echo(char **words, int max_words);
//B_cd
int		b_cd(char *direct, t_mshell *mshell);
//Executables
char	**arraydup(char **old);
void	executables(char **cmd, t_mshell *mshell);
int		free_mem(char **available, char *temp);
int		check_access(char *temp, char **available);
int		return_aux(char *temp, char **available);
//Pipe
int		token_less(t_cmds *cmds, int mode);
int		pipe_argument(char *str);
void	token_more(t_cmds *cmds, int mode);
void	handle_pipes(int num, int **pipefd, t_mshell *mshell, t_cmds *cmds);
void	reset_fds(t_mshell *mshell);
void	dup_fd(int fd);
//Words
char	**init_words(char *str);
int		check_pipe(char	**words, int count);
int		init_w_quote_aux(char *str, int *i, char *c);
int		nalloc_words(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		is_space(char c);
int		is_quote(char c);
int		is_special_char(char c);
int		is_double_special_char(char c1, char c2);
int		valid_words(char **words);
void	another_quote(int *i, char *str);
void	dollar_check(char *str, int *count);
void	init_dollar(char *str, int *j, char **words);
//Expand
char	*get_name(char *str);
char	*expand(char *str, t_mshell *mshell);
//Expand_env
char	*expand_env(char *str, t_mshell *mshell);
//Get_nsize
int		get_nsize(char *str, t_mshell *mshell);
//Get_env
char	*get_env(char *str, char **envir);
//Errors
int		error_cmd_not_found(t_cmds *cmds);
int		error_cd(char *cmd);
int		error_too_many_args(void);
//Alloc_words
char	**alloc_words(t_lexer *lexer, t_cmds *cmds);
//Clear_mem
void	clear_mem(t_mshell *mshell, t_cmds *cmds);
void	free_lexer(t_lexer *lexer);
void	free_envior(t_mshell *mshell);
void	free_array(char **array);
int		check_temp(char *temp, char **available);
void	free_available(char **available, int i);
void	free_redout(t_cmds *cmds);
//Signal
void	sig_continue(int signum);
void	reset_signals(void);
void	sigint_handle_child(int signum);
void	sig_fork(t_cmds cmds);
#endif // MINISHELL_H
