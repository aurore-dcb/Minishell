/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:04:51 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/31 15:04:50 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

#include <dirent.h>

// modifier le PATH ?
void builtin_cd(char *chemin)
{
    if (chdir(chemin) == -1)
    {
        perror("Error ");
        return ;
    }
}
