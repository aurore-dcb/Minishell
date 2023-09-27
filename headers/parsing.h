/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:09:52 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 17:20:52 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// quotes.c
int			closed_quotes(char *input, t_quotes *etat);
// parsing.c
int			is_meta(char c);
int			is_spaces(char c);
int			parsing(s_data *data);
// list.c
void		ft_lstadd_back_cmd_line(cmd_line **lst, cmd_line *new);
cmd_line	*ft_lstnew_cmd_line(int len);
cmd_line	*ft_lstlast_cmd_line(cmd_line *lst);
// split_pipe.c
int			nb_mots_cmd(char *str);
int			nb_lettre_cmd(char *s);
void		split2_pipe(char **input, cmd_line **cmd);
int			split_pipe(char *input, cmd_line **list);
// error_handling.c
int			error_begin_end_cmd(char *input);
int			error_double_pipe(char *input);
char		error_syntax(cmd_line **list);
int			error_syntax_alone(cmd_line **list);
int			error_pipe_token(char *input);
// expand.c
char		*ft_strcpy(char *dst, char *src, int dstsize);
int			count_char(char *s, s_data *data, token **token);
char		*apply_expand(char *res, char *word, s_data *data, token **token);
char		*ft_expand(char *word, s_data *data, token **token);
// expand_count.c
char		*existing_var(char *var, s_data *data, t_type type);
int			find_variable(char *s, s_data *data, token **token);
int			count_between_simple(char **s);
int			count_between_double(char **s, s_data *data, token **token);
// expand_apply.c
int			between_simple(char *res, char **word, int i);
int			between_double(char *res, char **word, s_data *data, int i);
int			out_of_quotes(char *res, char **word, s_data *data, int i);
char		*ft_trim(char *s, int len);
// expand_special.c
int			ft_strlen_expand(char *var);
void		new_words(char *var, token **token);
int			do_find(token **token, char *res, char *trim);
int			find_variable_special(char **s, s_data *data, token **token);
token		*ft_lstnew_token_special(char *var, token *current);
// split_word.c
void		ft_strcpy_pos(char *dst, char *src, int start, int end);
t_type		get_type_meta(char *word);
void		get_type(token *lst);
token		*ft_lstnew_token(cmd_line *list, int start, int end);
void		ft_lstadd_back_token(token **lst, token *new);
int			add_word(cmd_line *list);
int			split_word(cmd_line *list);
// get_end_word.c
int			get_end_word(char *cmd, int i);
int			end_except(char *cmd, int i);
// parse_env.c
int			copy_elem(char **split_res, char *nul_char, t_env *elem);
t_env		*ft_lstnew_env(char *data);
t_env		*ft_lstnew_env_equal(char *data);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
int			parse_env(char **env, s_data *data);
//list_env.c
t_env		*ft_lstnew_env(char *data);
t_env		*ft_lstnew_env_no_equal(char *data);
t_env		*ft_lstnew_env_equal(char *data);
int			ft_lstsize(t_env *lst);
int			len_var_env(char *s);
#endif