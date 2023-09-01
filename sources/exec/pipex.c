/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/09/01 10:28:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	initialise_pipex(pipex *pipex)
{
	pipex->paths = NULL;
	pipex->infile = -1;
	pipex->outfile = -1;
	// pipex->here_doc_file = -1;
	pipex->middle_cmd = NULL;
	pipex->middle_cmd_path = NULL;
	pipex->fd[0] = 0;
	pipex->fd[1] = 0;
}

int open_file(pipex *pipex, s_data *data)
{
	cmd_line *beg_cmd;
	token	*beg_token;
	
	beg_cmd = data->cmd;
	if (!beg_cmd)
		return (0);
	while (beg_cmd)
	{
		beg_token = beg_cmd->token;
		if (!beg_token)
			return (0);
		while (beg_token)
		{
			if (beg_token->type == 6)
				pipex->infile = open(beg_token->word, O_RDONLY);
			beg_token = beg_token->next;
		}
		beg_cmd = beg_cmd->next;
	}
	if (pipex->infile == -1)
		return (0);
	return (1);
}

int	parsing_pipex(pipex *pipex, s_data *data)
{
	pipex->paths = get_paths(&data->envp);
	if (!pipex->paths)
		return (ft_printf("ERROR -> Paths\n"), 0);
	if (!open_file(pipex, data))
		return (ft_printf("ERROR -> Can't open infile\n"), 0);
	printf("pipex->infile : %d\n", pipex->infile);
	// data->infile = open(argv[1], O_RDONLY);
	// if (data->infile == -1)
	// 	return (ft_printf("Error -> Can't create/open file\n"), 0);
	// data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0646);
	// if (data->outfile == -1)
	// {
	// 	close(data->infile);
	// 	ft_printf("Error -> Can't create/open file\n");
	// 	return (0);
	// }
	return (1);
}

int	ft_pipex(s_data *data)
{
	t_pid *pids;
	pipex pipex;
	// t_parsing	data;
	// t_cmd		*cmd;

	pids = NULL;
	// pipex = NULL;
	// cmd = NULL;
	// if (is_here_doc(argc, argv))
	// 	return (ft_here_doc(argv, argc, env, &cmd));
	// else
	// {
	initialise_pipex(&pipex);
	if (!parsing_pipex(&pipex, data))
		return (1);
		// return (error_free(&data, &cmd, &pids), 1);
	// if (!create_list_cmd(&cmd, argc, argv, 2))
	// 	return (error_free(&data, &cmd, &pids), 1);
	// cmd->in = data.infile;
	// if (!loop_process(&data, &pids, &cmd))
	// 	return (1);
	// wait_fct(&pids, &data, &cmd);
	// }
	return (0);
}