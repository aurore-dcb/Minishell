/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:36:36 by aducobu           #+#    #+#             */
/*   Updated: 2023/10/02 15:33:59 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		len;

	len = ft_strlen(s1) + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (0);
	res = ft_memcpy(res, s1, len);
	return (res);
}
