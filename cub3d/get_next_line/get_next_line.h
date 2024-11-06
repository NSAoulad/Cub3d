/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 15:16:21 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/06 17:38:11 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
// size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_strdup_g(char *s);
char	*ft_strjoin_g(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *str, const char *str2, size_t size);

#endif

// #ifndef GET_NEXT_LINE_H
// # define GET_NEXT_LINE_H

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 10
// # endif

// # include <errno.h>
// # include <fcntl.h>
// # include <stdarg.h>
// # include <stdint.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <unistd.h>

// char	*get_next_line(int fd);
// size_t	ft_strlen(const char *s);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strchr(const char *s, int c);
// char	*ft_strcpy(char *dst, const char *src, int size);
// int		ft_strncmp(const char *str, const char *str2, size_t size);

// #endif