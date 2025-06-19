/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:40:14 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/18 17:37:45 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 34
# endif

int		ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*get_buffer(char buffer[], int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*detele_all_after_newline(char *read_line);
int		ft_char_in_string(char *string, char a);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strcpy(char *goal, const char *start);
char	*strcpy_til_newline(char *buffer);

#endif
