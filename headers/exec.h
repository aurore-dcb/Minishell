/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/27 15:51:01 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// frees.c
void	free_tab(char **tab);
void	free_list(cmd_line *begin);
void	free_all(s_data *data);
void	free_env(t_env *env);
// frees2.c
void	free_pid(t_pid **pids);
void	free_elem_env(t_env *list);
void	free_no_buil(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
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
int		open_files(s_data *data);
// int		open_outfile(s_data *data);
t_file	*ft_lstlast_file(t_file *lst);
void	ft_lstadd_file(t_file **lst, t_file *new);
t_file	*ft_lstnew_file(int fd, int err, char *file);
void	add_outfiles(cmd_line *cmd);
// process.c
int		loop_process(s_data *data, t_pid **pids, pipex *pipex);
int		ft_process(pipex *pipex, t_pid **pids, cmd_line *cmd, s_data *data);
int		ft_child(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
void    no_builtins(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
// process_utils.c
char	**copy_to_tab(char **tab, t_env *tmp);
char	**list_to_tab(t_env **envp);
int		handle_hd(s_data *data, t_pid **pids, pipex *pipex, cmd_line	*tmp);
void	handle_point(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
void	do_dup(cmd_line *cmd, t_file *last_in, t_file *last_out);
// t_file	*ft_lstlast_file(t_outfile *lst);
// find_path.c
char	*find_path(char **paths, char *cmd);
// pids.c
t_pid	*ft_lstnew_pipex(pid_t pid);
int		ft_lstadd_back_pipex(t_pid **lst, t_pid *new);
// here_doc.c
int		is_here_doc(cmd_line *cmd);
int		ft_here_doc(cmd_line *cmd, pipex *pipex, s_data *data, t_pid **pids);
// error.c
void	error_file(t_file *in, s_data *data);
void	error_cmd(cmd_line *cmd, s_data *data);
void	error_token_gen(s_data *data, int tmp);
void	error_token(s_data *data, char c);
void	error_file_exec(char *cmd, s_data *data, int error);
// shlvl.c
void	handle_shlevel(s_data *data);
#endif