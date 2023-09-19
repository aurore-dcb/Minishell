/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:11:43 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/19 16:56:31 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// echo.c
int		verif_n(char **args);
int		builtin_echo(cmd_line *cmd);
// cd.c
char	*find_path_ret(t_env *envp, char *str);
int		search_path(t_env *envp, char *str);
int		builtin_cd(s_data *data);
void	print_oldpwd(s_data *data, int ret);
// cd_utils.c
char	*change_pwd(s_data *data);
int		change_oldpwd(s_data *data, char *ret);
int		error_path(s_data *data);
void	error_message(void);
// env.c
int		builtin_env(s_data *data);
// export.c
int		add_two_env(t_env *env, char *args, int to_equal);
int		add_no_equal(t_env *env, char *args);
int		do_export(s_data *data, int i, char **args);
int		builtin_export(s_data *data);
// export_utils.c
void	ft_swap(t_env *a, t_env *b);
t_env	*ft_sort_list(t_env *envex);
void	print_sorted_env(t_env *envex);
void	ft_lstreplace_env(t_env **lst, t_env *new);
void	ft_lstjoin_env(t_env **lst, t_env *new);
// export_utils2.c
int		is_inv(char *str);
int		has_plus(char *str);
int		in_env(t_env *env, char *key);
void	del_plus(char *str, char to_del);
// pwd.c
int		builtin_pwd(void);
// unset.c
void	del_var(t_env **head, char *arg);
int		builtin_unset(s_data *data);
// builtins.c
int		builtins_pipe(char *cmd, s_data *data, cmd_line *cmd_l);
int		builtins_no_pipe(cmd_line *cmd, s_data *data);
// exit.c
int		builtin_exit(s_data *data);
int		get_len_tab(char **str);
#endif