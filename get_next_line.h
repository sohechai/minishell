/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:36:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/02 18:56:18 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H
# define BUFFER_SIZE 2048
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

size_t			ft_len_until_n(const char *str);
char			*ft_strdup(const char *src);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_less_gnl(char **line, char *str);
int				get_next_line(int fd, char **line);
int				ft_check_error(char **line);

#endif
