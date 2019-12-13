/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:57:49 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/13 05:17:54 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

typedef struct		s_struct
{
	int				len;
	int				ret;
	int				pos;
	int				bool;
	char 			*buffer;
	char			*tmp;
	char			*s[OPEN_MAX];
}					t_struct;

int		ft_strlen(char *str);
char	*ft_freedup(char *src);
char	*ft_calloc(int count, int size);
char	*ft_strdup(char *src, int len);
char	*ft_substr(char *s, unsigned int start, size_t len, int bool);
char	*ft_strjoin(char *s1, char *s2, int len);
int		ft_charset(char *str);
int		get_next_line(int fd, char **line);
int		my_gnl(int fd, char **line, t_struct *v);

#endif
