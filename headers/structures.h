/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:07:30 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/31 15:08:31 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STUCTURES_H
#define STUCTURES_H

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

typedef struct cmd_line
{
	char			*cmd;
	char			**args;
	struct token	*token;
	struct cmd_line	*next;
}					cmd_line;

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*input;
	struct s_quotes	etat;
	struct cmd_line	*cmd;
	struct s_env	*envp;
	int				exit_status;
}					s_data;

#endif