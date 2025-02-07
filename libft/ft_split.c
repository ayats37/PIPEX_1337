/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:07:16 by taya              #+#    #+#             */
/*   Updated: 2024/11/06 10:51:59 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_subs(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

static int	ft_len_subs(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	ft_process_substrings(char **arr, char const *s, char c, int count)
{
	int	i;

	i = 0;
	while (*s && i < count)
	{
		if (*s != c && *s)
		{
			arr[i] = malloc((ft_len_subs(s, c) + 1) * sizeof(char));
			if (!arr[i])
			{
				while (i-- > 0)
					free(arr[i]);
				free(arr);
				return (0);
			}
			ft_strncpy(arr[i], s, ft_len_subs(s, c));
			arr[i][ft_len_subs(s, c)] = '\0';
			i++;
			s += ft_len_subs(s, c);
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count_subs(s, c);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!ft_process_substrings(arr, s, c, count))
		return (NULL);
	arr[count] = NULL;
	return (arr);
}
