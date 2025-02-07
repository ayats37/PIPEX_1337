/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:05:43 by taya              #+#    #+#             */
/*   Updated: 2024/11/03 13:57:29 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*arr;

	if (n == 0 || size == 0)
		return (malloc(0));
	if (n != 0 && size > SIZE_MAX / n)
		return (NULL);
	arr = malloc(n * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, n * size);
	return (arr);
}
