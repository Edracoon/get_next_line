/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:25:23 by marvin            #+#    #+#             */
/*   Updated: 2021/02/06 10:02:23 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnew(size_t size);
int			ft_strdel(char **ptr);
int			get_next_line(int fd, char **line);
int			ft_strlen(const char *str);
void		*ft_memalloc(size_t size);
void		*ft_memset(void *b, int c, size_t len);

#endif
