/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:09:52 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:56:48 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int			closed_quotes(char *input, t_quotes *etat);
int			is_meta(char c);
int			is_spaces(char c);
int			expansion(t_data *data);
int			error_pars(t_data *data);
int			parsing(t_data *data);
void		ft_lstadd_back_cmd_line(t_cmd_line **lst, t_cmd_line *new);
t_cmd_line	*ft_lstnew_cmd_line(int len);
t_cmd_line	*ft_lstlast_cmd_line(t_cmd_line *lst);
t_token		*ft_lstnew_token(t_cmd_line *list, int start, int end);
void		ft_lstadd_back_token(t_token **lst, t_token *new);
int			nb_between_quotes(char **str, int i);
int			nb_mots_cmd(char *str);
int			nb_lettre_cmd(char *s);
void		split2_pipe(char **input, t_cmd_line **cmd);
int			split_pipe(char *input, t_cmd_line **list);
int			error_begin_end_cmd(char *input);
int			error_pipe_token(char *input);
int			error_double_pipe(char *input);
int			error_syntax_alone(t_cmd_line **list);
char		error_syntax(t_cmd_line **list);
char		*ft_strcpy(char *dst, char *src, int dstsize);
int			count_char(char *s, t_data *data, t_token **token);
char		*apply_expand(char *res, char *word, t_data *data, t_token **token);
char		*trim_isspace(char const *s1, char const *set);
char		*ft_expand(char *word, t_data *data, t_token **token);
char		*ft_copy(t_env *begin, t_type type, char *var);
char		*existing_var(char *var, t_data *data, t_type type);
int			count_between_simple(char **s);
int			find_variable(char *s, t_data *data, t_token **token);
int			count_between_double(char **s, t_data *data, t_token **token);
int			between_simple(char *res, char **word, int i);
int			out_of_quotes(char *res, char **word, t_data *data, int i);
int			apply_out_quotes(char *res, char **word, t_data *data, int i);
int			between_double(char *res, char **word, t_data *data, int i);
char		*ft_trim(char *s, int len);
int			ft_strlen_expand(char *var);
int			do_find(t_token **token, char *res, char *trim);
int			find_variable_special(char **s, t_data *data, t_token **token);
t_token		*ft_lstnew_token_special(char *var, t_token *current);
void		new_words(char *var, t_token **token);
void		ft_strcpy_pos(char *dst, char *src, int start, int end);
t_type		get_type_meta(char *word);
void		get_type(t_token *lst);
int			add_word(t_cmd_line *list);
int			split_word(t_cmd_line *list);
int			end_except(char *cmd, int i);
char		is_quote(char c);
int			get_end_word(char *cmd, int i);
int			copy_elem(char **split_res, char *nul_char, t_env *elem);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
int			parse_env(char **env, t_data *data);
t_env		*ft_lstnew_env(char *data);
t_env		*ft_lstnew_env_no_equal(char *data);
t_env		*ft_lstnew_env_equal(char *data);
int			ft_lstsize(t_env *lst);
int			len_var_env(char *s);

#endif