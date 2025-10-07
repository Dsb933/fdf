/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsb <dsb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:49:35 by dsb               #+#    #+#             */
/*   Updated: 2025/04/30 18:04:13 by dsb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_t;
	size_t	i;
	size_t	j;
	char	*sub;

	if (!s1 || !s2)
		return (NULL);
	len_t = ft_strlen(s1) + ft_strlen(s2) + 1;
	sub = malloc(len_t);
	if (!sub)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		sub[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		sub[i + j] = s2[j];
		j++;
	}
	sub[i + j] = '\0';
	return (sub);
}
