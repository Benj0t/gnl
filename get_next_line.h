/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:57:49 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/09 17:27:53 by marvin           ###   ########.fr       */
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
	int				ret;
	int				pos;
	int				bool;
	char 			*buffer;
	char			*tmp;
	char			*s[OPEN_MAX];
}					t_struct;

int		ft_strlen(char *str);
char	*ft_freedup(char *src);
char	*ft_strnew(int nb);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, unsigned int start, size_t len, int bool);
char	*ft_strjoin(char *s1, char *s2);
int		ft_charset(char *str);
int		get_next_line(int fd, char **line);
int		my_gnl(int fd, char **line, t_struct *v);

#endif
