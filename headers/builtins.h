/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:11:43 by aducobu           #+#    #+#             */
/*   Updated: 2023/08/31 15:12:26 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

// pwd.c
void				builtin_pwd(char **env);
// env.c
void				builtin_env(char **env);
// cd.c
void				builtin_cd(char *chemin);
// echo.c
void				builtin_echo(char **cmd);

#endif