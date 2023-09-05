/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/05 10:21:20 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// frees.c
void	free_tab(char **tab);
void	free_list(cmd_line **begin);
void	free_all(cmd_line **cmd, char *input, pipex *pipex);
void	free_outfile(t_outfile **outfiles);
void	wait_fct(t_pid **pids, pipex *pipex, s_data *data);
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
int		open_outfile(pipex *pipex, s_data *data);
// process.c
int		loop_process(s_data *data, t_pid **pids, pipex *pipex);
int		ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data);
int		ft_child(cmd_line *cmd, pipex *pipex, s_data *data);
int	ft_lstsize(t_env *lst);
char **list_to_tab(t_env **envp);
t_outfile	*ft_lstlast_outfile(t_outfile *lst);
// find_path.c
char	*find_path(char **paths, char *cmd);
// pids.c
t_pid	*ft_lstnew_pipex(pid_t pid);
int		ft_lstadd_back_pipex(t_pid **lst, t_pid *new);

#endif