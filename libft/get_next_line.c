/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:15:10 by aducobu           #+#    #+#             */
/*   Updated: 2023/07/03 11:00:15 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!dst || !src)
		return (NULL);
	while (dst[i])
		i++;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_stash(char *stash, char *buf)
{
	char	*res;
	int		i;

	if (!stash && !buf)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (stash && stash[i])
	{
		res[i] = stash[i];
		i++;
	}
	i = 0;
	while (buf && buf[i])
	{
		res[i + ft_strlen(stash)] = buf[i];
		i++;
	}
	res[i + ft_strlen(stash)] = '\0';
	free(stash);
	return (res);
}

void	clean_buf(char *buf)
{
	int	i;

	i = 0;
	if (buf)
	{
		while (buf[i])
			buf[i++] = '\0';
	}
}

char	*create_stash(char *stash, int fd, char *buf)
{
	int	res;

	res = 1;
	while (is_new_line(stash) < 0 && res != 0)
	{
		res = read(fd, buf, BUFFER_SIZE);
		if (res == -1)
			return (NULL);
		buf[res] = '\0';
		if (res > 0)
		{
			stash = ft_strjoin_stash(stash, buf);
			if (!stash)
				return (NULL);
			clean_buf(buf);
		}
	}
	if (res == -1)
		return (NULL);
	return (stash);
}

char	*get_next_line(int fd, char *to_find)
{
	char		*ligne;
	static char	*stash;
	char		*buf;
	char		*inter;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stash = create_stash(stash, fd, buf);
	if (!stash)
		return (free(buf), NULL);
	free(buf);
	ligne = just_the_line(stash);
	stash = clean_stash(stash);
	if (!stash)
		return (free(ligne), NULL);
	if (!ligne)
		return (free(stash), NULL);
	inter = ft_substr(ligne, 0, ft_strlen(ligne) - 1);
	if (!inter)
		return (ft_printf("ERREUR\n"), NULL);
	if (ft_strcmp(inter, to_find) == 0)
		return (free(stash), free(inter), free(ligne), NULL);
	return (free(inter), ligne);
}
