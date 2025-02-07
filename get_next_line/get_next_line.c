/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 03:55:55 by taya              #+#    #+#             */
/*   Updated: 2024/11/20 15:35:54 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buffer)
{
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	buffer = ft_check_for_read(fd, buffer);
	if (buffer && buffer[0] == '\0')
		return (free(buffer), NULL);
	return (buffer);
}

char	*ft_check_for_read(int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*new_buffer;
	char	*temp;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (free(buffer), NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(temp), NULL);
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		free(buffer);
		if (!new_buffer)
			return (free(temp), NULL);
		buffer = new_buffer;
	}
	free(temp);
	return (buffer);
}

char	*ft_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strncpy(line, buffer, i);
	line[i] = '\0';
	return (line);
}

char	*ft_save_leftover(char *buffer)
{
	char	*after_newline;
	char	*leftover;

	after_newline = ft_strchr(buffer, '\n');
	if (!after_newline)
	{
		free(buffer);
		return (NULL);
	}
	after_newline++;
	leftover = ft_strdup(after_newline);
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_save_leftover(buffer);
	return (line);
}
