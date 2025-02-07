/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:07:31 by taya              #+#    #+#             */
/*   Updated: 2024/11/03 15:23:57 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (n == 0)
		return (ft_strlen(s2));
	j = (size_t)ft_strlen(s1);
	k = (size_t)ft_strlen(s2);
	if (n <= j)
	{
		return (n + k);
	}
	while (s2[i] && j + i < n - 1)
	{
		s1[j + i] = s2[i];
		i++;
	}
	s1[j + i] = '\0';
	return (j + k);
}
