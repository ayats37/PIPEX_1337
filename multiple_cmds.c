/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:54:14 by taya              #+#    #+#             */
/*   Updated: 2025/02/07 15:26:58 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_data *data, int pipe_fd[][2])
{
	int	fd;

	if (data->here_doc)
		fd = open("file", O_RDONLY);
	else
		fd = open(data->argv[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipe_fd[data->i][1], STDOUT_FILENO);
}

void	last_cmd(t_data *data, int pipe_fd[][2])
{
	int	fd;

	fd = ft_open_file_bonus(data->argv[data->argc - 1], 1, data->here_doc);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(pipe_fd[data->i - 1][0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	middle_cmd(t_data *data, int pipe_fd[][2])
{
	dup2(pipe_fd[data->i - 1][0], STDIN_FILENO);
	dup2(pipe_fd[data->i][1], STDOUT_FILENO);
}

void	execute_commands(t_data *data)
{
	char	*cmd_path;
	char	**cmd_args;

	if (data->here_doc)
		cmd_args = ft_split(data->argv[data->i + 3], ' ');
	else
		cmd_args = ft_split(data->argv[data->i + 2], ' ');
	if (cmd_args == NULL)
	{
		perror("ft_split failed");
		exit(1);
	}
	cmd_path = find_cmd_path(cmd_args[0], data->env);
	if (!cmd_path)
	{
		perror("command not found");
		ft_free_arr(cmd_args);
		exit(1);
	}
	execve(cmd_path, cmd_args, data->env);
	perror("execve failed");
	free(cmd_path);
	ft_free_arr(cmd_args);
	exit(1);
}

void	child(t_data *data, int pipe_fd[][2])
{
	int	j;

	j = 0;
	if (data->i == 0)
		first_cmd(data, pipe_fd);
	else if (data->i == data->cmd_nbrs - 1)
		last_cmd(data, pipe_fd);
	else
		middle_cmd(data, pipe_fd);
	while (j < data->cmd_nbrs - 1)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
		j++;
	}
	if (data->argv[data->i + 3] && data->argv[data->i + 3][0] != '\0'
		&& data->here_doc)
		execute_commands(data);
	else if (data->argv[data->i + 2] && data->argv[data->i + 2][0] != '\0')
		execute_commands(data);
	else
	{
		perror("comamnd not found");
		exit(1);
	}
}
