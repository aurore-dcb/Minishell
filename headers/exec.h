/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:41:21 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 11:25:03 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	free_tab(char **tab);
void	free_cmd_in(t_file *in);
void	free_list(t_cmd_line *begin);
void	free_all(t_data *data);
void	wait_fct(t_pid **pids, t_data *data);
void	free_elem_env(t_env *list);
void	free_env(t_env *env);
void	fr_no_buil(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids);
void	free_pid(t_pid **pids);
void	initialize(t_data *data);
char	*prompt(void);
int		nb_arg(t_cmd_line *list);
void	fill_arg(t_cmd_line *list);
int		tab_cmd(t_cmd_line **list);
char	**new_tab(char **old_tab, int old_len);
void	parse_error(t_data *data);
void	initialise_pipex(t_pipex *pipex);
int		parsing_pipex(t_pipex *pipex, t_data *data);
int		ft_lstsize_cmd(t_cmd_line *lst);
int		ft_pipex(t_data *data);
char	*ft_trim_pipex(char *s);
char	**get_paths(t_env **envp);
void	ft_lstadd_file(t_file **lst, t_file *new);
t_file	*ft_lstnew_file(int fd, int err, char *file);
t_file	*ft_lstlast_file(t_file *lst);
void	add_infiles(t_cmd_line *cmd);
int		open_files(t_data *data);
void	add_outfiles(t_cmd_line *cmd);
int		loop_process(t_data *data, t_pid **pids, t_pipex *pipex);
void	ft_parent(t_pid **pids, pid_t pid, t_cmd_line *cmd, t_file *last_in);
int		ft_process(t_pipex *pipex, t_pid **pids, t_cmd_line *cmd, t_data *data);
void	no_built(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids);
int		ft_child(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids);
char	**copy_to_tab(char **tab, t_env *tmp);
char	**list_to_tab(t_env **envp);
int		handle_hd(t_data *data, t_pid **pids, t_pipex *pipex, t_cmd_line *tmp);
void	handle_pt(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids);
void	do_dup(t_cmd_line *cmd, t_file *last_in, t_file *last_out);
char	*ft_trim_paths(char *s);
char	*find_path(char **paths, char *cmd);
t_pid	*ft_lstnew_pipex(pid_t pid);
int		ft_lstadd_back_pipex(t_pid **lst, t_pid *new);
int		is_here_doc(t_cmd_line *cmd);
int		read_standart(t_pipex *pipex, char *to_find);
int		standart_input(t_cmd_line *cmd, t_pipex *pipex);
int		proc_hd(t_pipex *pipex, t_cmd_line *cmd, t_data *data, t_pid **pids);
int		ft_hd(t_cmd_line *cmd, t_pipex *pipex, t_data *data, t_pid **pids);
void	error_file(t_file *in, t_data *data);
void	error_cmd(t_cmd_line *cmd, t_data *data);
void	error_token_gen(t_data *data, int tmp);
void	error_token(t_data *data, char c);
void	error_file_exec(char *cmd, t_data *data, int error);
int		get_shlvl(t_data *data);
int		is_shlvl(t_data *data);
char	*get_shvalue(t_data *data);
void	handle_shlevel(t_data *data);

#endif