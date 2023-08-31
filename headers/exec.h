/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/31 15:13:27 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// frees.c
void				free_tab(char **tab);
void				free_list(cmd_line **begin);
void				free_all(cmd_line **cmd, char *input);
// main.c
void				initialize(s_data *data);
// exec_utils.c
int					nb_arg(cmd_line *list);
void				fill_arg(cmd_line *list);
int					tab_cmd(cmd_line **list);
// parse_env.c
int					parse_env(char **env, t_env **envp);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
t_env				*ft_lstnew_env(char *data);
// error.c


#endif