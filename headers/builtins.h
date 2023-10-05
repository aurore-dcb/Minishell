/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:11:43 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/05 17:49:23 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		test_arg(char **args, int i);
int		nb_option(char **args);
int		verif_n(char **args);
void	print_echo(t_cmd_line *cmd, int i, int y);
int		builtin_echo(t_cmd_line *cmd);
char	*find_path_ret(t_env *envp, char *str);
int		search_path(t_env *envp, char *str);
void	print_oldpwd(t_data *data, int ret);
int		builtin_cd(t_cmd_line *cmd, t_data *data);
char	*change_pwd(t_data *data);
int		change_oldpwd(t_data *data, char *ret);
int		error_path(t_cmd_line *cmd);
void	error_message(void);
int		builtin_env(t_data *data);
int		add_to_envp(char *args, int to_equal, t_data *data);
int		add_to_envex(char *args, int to_equal, t_data *data);
int		add_no_equal(t_env *env, char *args);
int		handle_equal(t_data *data, int i, char **args, int ret_inv);
int		do_export(t_data *data, int i, char **args);
int		builtin_export(t_cmd_line *cmd, t_data *data);
void	ft_swap(t_env *a, t_env *b);
t_env	*ft_sort_list(t_env *envex);
void	print_sorted_env(t_env *envex);
void	ft_lstreplace_env(t_env **lst, t_env *new);
void	ft_lstjoin_env(t_env **lst, t_env *new);
int		is_inv(char *str);
int		has_plus(char *str);
int		in_env(t_env *env, char *key);
void	del_plus(char *str, char to_del);
int		builtin_pwd(void);
void	del_var(t_env **head, char *arg);
int		builtin_unset(t_cmd_line *cmd, t_data *data);
int		builtins_pipe(char *cmd, t_data *data, t_cmd_line *cmd_l);
int		builtins_no_pipe(t_cmd_line *cmd, t_data *data);
void	do_join(t_env *list, t_env *new);
int		is_str_digit(char *str);
void	num_exit(char *str, int error, t_data *data);
int		get_len_tab(char **str);
int		builtin_exit(t_cmd_line *cmd, t_data *data);

#endif