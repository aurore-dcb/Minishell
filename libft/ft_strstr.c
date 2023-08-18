/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:07:58 by aurore            #+#    #+#             */
/*   Updated: 2023/06/29 14:59:34 by aducobu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;
	char	*x;

	if (!str || to_find[0] == '\0')
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == to_find[0])
		{
			x = &str[i];
			j = 0;
			while (str[i] == to_find[j] && to_find[j] != '\0' && str[i] != '\0')
			{
				j++;
				i++;
			}
			if (j == ft_strlen(to_find))
				return (x);
		}
		i++;
	}
	return (0);
}
