/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:52:24 by taya              #+#    #+#             */
/*   Updated: 2025/02/06 20:38:23 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	execute_command(char *cmd, char **env)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
	{
		perror("ft_split failed");
		exit(EXIT_FAILURE);
	}
	cmd_path = find_cmd_path(cmd_args[0], env);
	if (!cmd_path)
	{
		ft_free_arr(cmd_args);
		ft_putstr_fd("command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_args, env);
	perror("execve failed");
	free(cmd_path);
	ft_free_arr(cmd_args);
	exit(EXIT_FAILURE);
}

void	first_child(char **argv, int *pipe_fd, char **env)
{
	int	fd;

	fd = ft_open_file(argv[1], 0);
	if (fd == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (argv[2] && argv[2][0] != '\0')
		execute_command(argv[2], env);
	else
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
}

void	second_child(char **argv, int *pipe_fd, char **env)
{
	int	fd;

	fd = ft_open_file(argv[4], 1);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (argv[3] && argv[3][0] != '\0')
		execute_command(argv[3], env);
	else
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		status;

	check_args(argc);
	handle_pipe(pipe_fd);
	pid1 = create_process();
	if (pid1 == 0)
		first_child(argv, pipe_fd, env);
	pid2 = create_process();
	if (pid2 == 0)
		second_child(argv, pipe_fd, env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
