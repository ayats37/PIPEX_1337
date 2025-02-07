/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:04:30 by taya              #+#    #+#             */
/*   Updated: 2025/02/06 22:01:41 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_input(t_data *data)
{
	if (data->here_doc)
	{
		if (data->argc < 6)
		{
			perror("Usage: ./pipex here_doc LIMITER cm1 cmd2 ... file");
			exit(1);
		}
		data->cmd_nbrs = data->argc - 4;
	}
	else
	{
		if (data->argc < 5)
		{
			perror("Usage: ./pipex infile cmd1 cmd2 ... outfile");
			exit(1);
		}
		data->cmd_nbrs = data->argc - 3;
	}
}

void	create_pipes(t_data *data, int pipe_fd[][2])
{
	int	i;

	i = 0;
	while (i < data->cmd_nbrs - 1)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("pipe failed");
			exit(1);
		}
		i++;
	}
}

void	create_children(t_data *data, int pipe_fd[][2])
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->cmd_nbrs)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		if (pid == 0)
		{
			data->i = i;
			child(data, pipe_fd);
		}
		i++;
	}
}

void	close_pipes(t_data *data, int pipe_fd[][2])
{
	int	i;

	i = 0;
	while (i < data->cmd_nbrs - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	wait_children(t_data *data, int *status)
{
	int	i;

	i = 0;
	while (i < data->cmd_nbrs)
	{
		wait(status);
		i++;
	}
}
