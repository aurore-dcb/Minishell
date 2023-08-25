/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/25 13:18:30 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// -------------------- parsing -------------------- //

typedef enum type
{
	NONE,         //defaut set
	ARG,          //word
	FILE_IN,      //word == '<'
	HERE_DOC,     // word == '<<'
	FILE_OUT,     //word == '>'
	FILE_OUT_SUR, //word == '>>'
	OPEN_FILE,    // word following '<'
	LIMITOR,      // word following '<<'
	EXIT_FILE,    // word followinf '>'
	EXIT_FILE_RET // word following '>>'
}					t_type;

typedef struct s_quotes
{
	int				simple;
	int				doubl;
}					t_quotes;

typedef struct token
{
	char			*word;
	t_type			type;
	struct token	*next;
	struct token	*previous;
}					token;

typedef struct cmd_line
{
	char			*cmd;
	struct token	*token;
	struct cmd_line	*next;
}					cmd_line;

// quotes.c
int					closed_quotes(char *input, t_quotes *etat);
// split_meta.c
char				**split_meta(char *input, char c);
// parsing.c
int					parsing(char *input, char **env, cmd_line **list);
// list.c
void				ft_lstadd_back_cmd_line(cmd_line **lst, cmd_line *new);
cmd_line			*ft_lstnew_cmd_line(int len);
cmd_line			*ft_lstlast_cmd_line(cmd_line *lst);
// split_pipe.c
int					nb_mots_cmd(char *str);
int					nb_lettre_cmd(char *s);
void				split2_pipe(char **input, cmd_line **cmd);
int					split_pipe(char *input, cmd_line **list);
// error_handling.c
int					error_begin_end_cmd(char *input);
int					error_double_pipe(char *input);
// expand.c
// char				*ft_expand(char *word);
// split_word.c
void				ft_strcpy_pos(char *dst, char *src, int start, int end);
t_type				get_type_meta(char *word);
void				get_type(token *lst);
token				*ft_lstnew_token(cmd_line *list, int start, int end);
void				ft_lstadd_back_token(token **lst, token *new);
int					add_word(cmd_line *list);
void				split_word(cmd_line *list);

// -------------------- exec -------------------- //

// pwd.c
void				builtin_pwd(char **env);
// env.c
void				builtin_env(char **env);
// cd.c
void				builtin_cd(char *chemin);
// echo.c
void				builtin_echo(char **cmd);
// frees.c
void				free_tab(char **tab);
void				free_list(cmd_line **begin);

#endif