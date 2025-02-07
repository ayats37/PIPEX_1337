/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:06:51 by taya              #+#    #+#             */
/*   Updated: 2024/11/03 16:32:43 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *array, int value, size_t size)
{
	unsigned char	*arr;
	unsigned char	change_value;
	unsigned int	i;

	arr = (unsigned char *)array;
	change_value = (unsigned char)value;
	i = 0;
	while (i < size)
	{
		arr[i] = change_value;
		i++;
	}
	return (array);
}
