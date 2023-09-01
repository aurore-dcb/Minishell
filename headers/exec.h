/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 13:56:35 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// frees.c
void	free_tab(char **tab);
void	free_list(cmd_line **begin);
void	free_all(cmd_line **cmd, char *input);
// main.c
void	initialize(s_data *data);
// exec_utils.c
int		nb_arg(cmd_line *list);
void	fill_arg(cmd_line *list);
int		tab_cmd(cmd_line **list);

// pipex.c
void	initialise_pipex(pipex *pipex);
int		parsing_pipex(pipex *pipex, s_data *data);
int		ft_pipex(s_data *data);
// get_paths.c
char	**get_paths(t_env **envp);
// files.c
int		open_infile(pipex *pipex, s_data *data);

#endif