/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:07:20 by taya              #+#    #+#             */
/*   Updated: 2024/11/20 15:35:49 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_save_leftover(buffer[fd]);
	return (line);
}
