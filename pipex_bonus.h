/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:46:19 by taya              #+#    #+#             */
/*   Updated: 2025/02/07 15:27:10 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef MAX_PIPES
#  define MAX_PIPES 10240
# endif

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
	int		cmd_nbrs;
	int		i;
	int		here_doc;
}			t_data;

int			ft_open_file_bonus(const char *file, int mode, int here_doc);
char		*get_path(char **env);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
void		ft_free_arr(char **arr);
char		*get_path(char **env);
char		**split_cmd(char *cmd);
char		**get_paths(char **env);
char		*build_path(char *path, char *cmd);
char		*check_paths(char **paths, char *cmd);
char		*find_cmd_path(char *cmd, char **env);
void		first_cmd(t_data *data, int pipe_fd[][2]);
void		last_cmd(t_data *data, int pipe_fd[][2]);
void		middle_cmd(t_data *data, int pipe_fd[][2]);
void		execute_commands(t_data *data);
void		child(t_data *data, int pipe_fd[][2]);
void		check_input(t_data *data);
void		create_pipes(t_data *data, int pipe_fd[][2]);
void		create_children(t_data *data, int pipe_fd[][2]);
void		close_pipes(t_data *data, int pipe_fd[][2]);
void		wait_children(t_data *data, int *status);
void		here_doc(t_data *data);

#endif