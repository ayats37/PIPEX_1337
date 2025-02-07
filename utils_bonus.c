/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:09:51 by taya              #+#    #+#             */
/*   Updated: 2025/01/21 22:12:04 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_file(const char *file, int mode)
{
	int	fd;

	fd = 0;
	if (mode == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror("error opening file");
			return (-1);
		}
	}
	else if (mode == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("error opening file");
			return (-1);
		}
	}
	return (fd);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char	**command;
	char	**paths;
	char	*result;

	command = split_cmd(cmd);
	if (!command)
		return (NULL);
	paths = get_paths(env);
	if (!paths)
	{
		ft_free_arr(command);
		return (NULL);
	}
	result = check_paths(paths, command[0]);
	ft_free_arr(paths);
	ft_free_arr(command);
	return (result);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
