/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:07:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/22 15:55:51 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STUCTURES_H
# define STUCTURES_H

typedef enum type
{
	NONE,         //defaut set
	ARG,          //word
	FILE_IN,      //word == '<'
	HERE_DOC,     // word == '<<'
	FILE_OUT,     //word == '>'
	FILE_OUT_SUR, //word == '>>'
	OPEN_FILE,    // word following '<'
	LIMITOR,      // word following '<<'
	EXIT_FILE,    // word following '>'
	EXIT_FILE_RET // word following '>>'
}					t_type;

typedef struct s_quotes
{
	int				simple;
	int				doubl;
}					t_quotes;

typedef struct token
{
	char			*word;
	t_type			type;
	struct token	*next;
	struct token	*previous;
}					token;

typedef struct s_file
{
	int				fd;
	int				r_no;
	struct s_file	*next;
}					t_file;

typedef struct cmd_line
{
	struct s_file	*infile;
	struct s_file	*outfile;
	int				fd[2];
	char			*cmd;
	char			**args;
	int				error;
	struct token	*token;
	struct cmd_line	*next;
}					cmd_line;

typedef struct s_env
{
	char			*key;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*input;
	struct s_quotes	etat;
	struct cmd_line	*cmd;
	struct s_env	*envp;
	struct s_env	*envex;
	char			**tab_env;
	int				exit_status;
}					s_data;

// -------------- PIPEX -------------- //

typedef struct s_pipex_data
{
	char			**paths;
	int				infile;
	char			*middle_cmd_path;
	int				here_doc_file;
}					pipex;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}					t_pid;

#endif