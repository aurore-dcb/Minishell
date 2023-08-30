/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/30 13:13:38 by aducobu          ###   ########.fr       */
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

typedef struct s_data
{
	char			*input;
	struct s_quotes	etat;
	struct cmd_line	*cmd;
	char			**env;
	int				exit_status;
}					s_data;

// quotes.c
int					closed_quotes(char *input, t_quotes *etat);
// split_meta.c
int					is_meta(char c);
char				**split_meta(char *input, char c);
// parsing.c
int					parsing(s_data *data);
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
int					error_syntax(cmd_line **list);
// expand.c
char				*ft_strcpy(char *dst, char *src, int dstsize);
char				*ft_trim(char *s, int len);
int					count_char(char *s, s_data *data);
char				*apply_expand(char *res, char *word, s_data *data);
char				*ft_expand(char *word, s_data *data);
// expand_count.c
char				*existing_var(char *var, char **env);
int					len_var_env(char *s);
int					find_variable(char *s, char **env, int exit_status);
int					count_between_simple(char **s);
int					count_between_double(char **s, s_data *data);
// expand_apply.c
int					between_simple(char *res, char **word, int i);
int					between_double(char *res, char **word, char **env, int i);
int					out_of_quotes(char *res, char **word, s_data *data, int i);
// split_word.c
void				ft_strcpy_pos(char *dst, char *src, int start, int end);
t_type				get_type_meta(char *word);
void				get_type(token *lst);
token				*ft_lstnew_token(cmd_line *list, int start, int end);
void				ft_lstadd_back_token(token **lst, token *new);
int					add_word(cmd_line *list);
int					get_end_word(char *cmd, int i);
int					split_word(cmd_line *list);

// -------------------- exec -------------------- //

// frees.c
void				free_tab(char **tab);
void				free_list(cmd_line **begin);
void				free_all(cmd_line **cmd, char *input);
// error.c

//
void				initialize(s_data *data);

// -------------------- builtins.c -------------------- //

// pwd.c
void				builtin_pwd(char **env);
// env.c
void				builtin_env(char **env);
// cd.c
void				builtin_cd(char *chemin);
// echo.c
void				builtin_echo(char **cmd);

#endif