/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:32 by taya              #+#    #+#             */
/*   Updated: 2025/02/07 15:06:41 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_data *data)
{
	char	*line;
	int		fd;

	fd = open("file", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, data->argv[2], ft_strlen(data->argv[2])) == 0
			&& line[ft_strlen(data->argv[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		pipe_fd[MAX_PIPES][2];
	int		status;

	data.argc = argc;
	data.argv = argv;
	data.env = env;
	data.here_doc = (argc > 1 && !ft_strncmp(argv[1], "here_doc", 8));
	check_input(&data);
	if (data.cmd_nbrs > MAX_PIPES)
		return (1);
	if (data.here_doc)
		here_doc(&data);
	create_pipes(&data, pipe_fd);
	create_children(&data, pipe_fd);
	close_pipes(&data, pipe_fd);
	wait_children(&data, &status);
	unlink("file");
	return (WEXITSTATUS(status));
}
