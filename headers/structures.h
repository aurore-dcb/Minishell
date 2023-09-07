/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:07:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/07 10:52:51 by aducobu          ###   ########.fr       */
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
}						t_type;

typedef struct s_quotes
{
	int					simple;
	int					doubl;
}						t_quotes;

typedef struct token
{
	char				*word;
	t_type				type;
	struct token		*next;
	struct token		*previous;
}						token;

typedef struct cmd_line
{
	int					in;
	int					out;
	char				*cmd;
	char				**args;
	struct token		*token;
	struct cmd_line		*next;
}						cmd_line;

typedef struct s_env
{
    char            *key;
    char            *data;
    struct s_env    *next;
}                    t_env;

typedef struct s_data
{
	char				*input;
	struct s_quotes		etat;
	struct cmd_line		*cmd;
	struct s_env		*envp;
	struct s_env    *envex;
	int					exit_status;
}						s_data;

typedef struct s_outfile
{
	int					outfile;
	struct s_outfile	*next;
}						t_outfile;

// -------------- PIPEX -------------- //

typedef struct s_pipex_data
{
	char				**paths;
	int					fd[2];
	int					infile;
	t_outfile			*outfiles;
	char				**middle_cmd;
	char				*middle_cmd_path;
	//here_doc
}						pipex;

typedef struct s_pid
{
	pid_t				pid;
	struct s_pid		*next;
}						t_pid;

#endif