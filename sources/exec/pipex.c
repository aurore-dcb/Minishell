/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:39:05 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/31 15:40:01 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	pipex(int argc, char **argv, char **env)
{
	t_parsing	data;
	t_pid		*pids;
	t_cmd		*cmd;

	pids = NULL;
	cmd = NULL;
	if (is_here_doc(argc, argv))
		return (ft_here_doc(argv, argc, env, &cmd));
	else
	{
		initialise_data(&data, argc, argv, env);
		if (!parsing(argc, argv, env, &data))
			return (error_free(&data, &cmd, &pids), 1);
		if (!create_list_cmd(&cmd, argc, argv, 2))
			return (error_free(&data, &cmd, &pids), 1);
		cmd->in = data.infile;
		if (!loop_process(&data, &pids, &cmd))
			return (1);
		wait_fct(&pids, &data, &cmd);
	}
}