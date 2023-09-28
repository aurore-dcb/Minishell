/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:07:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/28 10:41:07 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum s_type
{
	NONE,
	ARG,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_SUR,
	OPEN_FILE,
	LIMITOR,
	EXIT_FILE,
	EXIT_FILE_RET
}	t_type;

typedef struct s_quotes
{
	int				simple;
	int				doubl;
}					t_quotes;

typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_file
{
	int				fd;
	int				r_no;
	char			*name;
	struct s_file	*next;
}					t_file;

typedef struct s_cmd_line
{
	struct s_file		*infile;
	struct s_file		*outfile;
	int					fd[2];
	char				*cmd;
	char				**args;
	int					error;
	struct s_token		*token;
	struct s_cmd_line	*next;
}						t_cmd_line;

typedef struct s_env
{
	char			*key;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char				*input;
	struct s_quotes		etat;
	struct s_cmd_line	*cmd;
	struct s_env		*envp;
	struct s_env		*envex;
	char				**tab_env;
	int					exit_status;
}						t_data;

typedef struct s_pipex
{
	char			**paths;
	int				infile;
	char			*middle_cmd_path;
	int				here_doc_file;
}					t_pipex;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}					t_pid;

#endif