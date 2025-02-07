/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 03:27:15 by taya              #+#    #+#             */
/*   Updated: 2025/01/20 05:33:43 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_open_file(const char *file, int mode);
char	*get_path(char **env);
void	first_child(char **argv, int *pipe_fd, char **env);
void	second_child(char **argv, int *pipe_fd, char **env);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
void	ft_free_arr(char **arr);
char	*get_path(char **env);
char	**split_cmd(char *cmd);
char	**get_paths(char **env);
char	*build_path(char *path, char *cmd);
char	*check_paths(char **paths, char *cmd);
char	*find_cmd_path(char *cmd, char **env);
void	check_args(int argc);
void	handle_pipe(int *pipe_fd);
pid_t	create_process(void);
void	execute_command(char *cmd, char **env);

#endif
