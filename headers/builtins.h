/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:11:43 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/07 10:35:10 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// pwd.c
void	builtin_pwd(s_data *data);
// env.c
void	builtin_env(s_data *data);
// cd.c
int		build_cd(s_data *data);
// echo.c
int		len_tab(char **cmd);
void	builtin_echo(char **cmd);
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
// export_utils2.c
int		is_inv(char *str);
int		has_plus(char *str);
int		in_env(t_env *env, char *key);
// unset.c
void	del_var(t_env **head, char *arg);
void	builtin_unset(s_data *data);
#endif