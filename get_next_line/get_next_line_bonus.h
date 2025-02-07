/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:08:19 by taya              #+#    #+#             */
/*   Updated: 2024/11/20 15:40:12 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif
# ifndef MAX_FD
#  define MAX_FD 10240
# endif

char	*ft_read(int fd, char *buffer);
char	*ft_line(char *buffer);
char	*ft_save_leftover(char *buffer);
char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dest, const char *src, int len);
char	*ft_check_for_read(int fd, char *buffer);
#endif