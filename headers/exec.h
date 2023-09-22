/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 14:14:20 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// frees.c
void	free_tab(char **tab);
void	free_list(cmd_line *begin);
void	free_all(s_data *data);
void	free_env(t_env *env);
void	free_pid(t_pid **pids);
// frees2.c
void	free_elem_env(t_env *list);
// void	free_outfile(t_outfile **outfiles);
void	wait_fct(t_pid **pids, s_data *data);
// main.c
void	initialize(s_data *data);
// exec_utils.c
int		nb_arg(cmd_line *list);
void	fill_arg(cmd_line *list);
int		tab_cmd(cmd_line **list);
char	**new_tab(char **old_tab, int old_len);
// pipex.c
void	initialise_pipex(pipex *pipex);
int		parsing_pipex(pipex *pipex, s_data *data);
int		ft_pipex(s_data *data);
int		ft_lstsize_cmd(cmd_line *lst);
// get_paths.c
char	**get_paths(t_env **envp);
// files.c
int		open_infile(s_data *data);
int		open_outfile(s_data *data);
t_infile	*ft_lstlast_infile(t_infile *lst);
void	ft_lstadd_back_infile(t_infile **lst, t_infile *new);
t_infile	*ft_lstnew_infile(int fd, int err);
// t_infile	*ft_lstnew_infile(char *file);
// process.c
int		loop_process(s_data *data, t_pid **pids, pipex *pipex);
int		ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data);
int		ft_child(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
void    error_file_exec(char *cmd, s_data *data, int error);
int		ft_lstsize(t_env *lst);
char	**list_to_tab(t_env **envp);
// t_outfile	*ft_lstlast_outfile(t_outfile *lst);
// find_path.c
char	*find_path(char **paths, char *cmd);
// pids.c
t_pid	*ft_lstnew_pipex(pid_t pid);
int		ft_lstadd_back_pipex(t_pid **lst, t_pid *new);
// here_doc.c
int		is_here_doc(cmd_line *cmd);
int		ft_here_doc(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
// error.c
void	error_file(cmd_line *cmd, t_infile *in, s_data *data, t_type type);
char	*get_info_cmd(cmd_line *beg_cmd, t_type type);
void	error_cmd(cmd_line *cmd, s_data *data);
void	error_token_gen(s_data *data, int tmp);
void	error_token(s_data *data, char c);
// shlvl.c
void	handle_shlevel(s_data *data);
#endif