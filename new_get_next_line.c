/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:51:24 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/03 18:55:55 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i])
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (src[++i])
		str[i] = src[i];
	str[i] = '\0';
	free(src);
	return (str);
}

char *ft_strnew(int nb)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * (nb + 1))))
		return(NULL);
	str[nb] = '\0';
	return(str);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int bool)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || (!(str = (char *)malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	if (!((unsigned int)ft_strlen(s) < start))
		while (len-- > 0 && i < (size_t)ft_strlen(s))
			str[i++] = s[start++];
	str[i] = '\0';
	if (bool == 1)
		free(s);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*pt;
	int		i;
	int		j;
	int		s1len;
	int		s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if ((!s1 || !s2) ||
		(!(pt = malloc(sizeof(char) * (s1len + s2len + 1)))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		pt[i++] = s1[j++];
	j = 0;
	while (s2[j])
		pt[i++] = s2[j++];
	pt[i] = '\0';0
	free(s1);
	free(s2);
	return (pt);
}

int		ft_charset(char *str)
{
	int i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int my_gnl(int fd, char **line, t_struct *v)
{
	while ((v->ret = read(fd, v->buffer, BUFFER_SIZE) > 0) && ((v->pos = ft_charset(v->s[fd])) < 0))
		if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer)) || !(v->s[fd] = ft_strdup(v->tmp)) || !(v->buffer = ft_strnew(BUFFER_SIZE)))
			return(-1);
	free(v->buffer);
	if (v->pos >= 0)
	{
		*line = ft_substr(v->s[fd], 0, v->pos, 0);
		v->tmp = ft_substr(v->s[fd], v->pos, ft_strlen(v->s[fd]) - v->pos, 1);
		v->s[fd] = ft_strdup(v->tmp);
		return(1);
	}
	if (v->ret == 0)
	{
		line = ft_strdup(v->tmp);
		return(0);
	}
	else
	{
		free(line);
		free(v->s[fd]);
		return (-1);
	}
	
	
}
int		get_next_line(int fd, char **line)
{
	static t_struct v;

	if (!(v.buffer = ft_strnew(BUFFER_SIZE)));
		return (-1);
	if (!v.bool)
	{
		if (!(v.s[fd] = ft_strnew(BUFFER_SIZE)));
			return (-1);
		v.bool = 1;
	}
	if ((v.pos = ft_charset(v.s[fd])) >= 0)
	{
		(*line) ? free(*line) : NULL;
		if (!(line = ft_substr(v.s[fd], 0, v.pos, 0);) || !(v.tmp = ft_substr(v.s[fd], v.pos, ft_strlen(v.s[fd]) - v.pos, 1)))
			return (-1);
		return ((v.s[fd] = ft_strdup(v.tmp)) ? 1 : -1);
	}
	if (v.ret == 0 && ft_strlen(v.s[fd]) != 0 && v.pos == -1)
	{
		(*line) ? free(*line) : NULL;
		return ((*line = ft_strdup(v.s[fd])) ? 0 : -1);
	}
	return (my_gnl(fd, line, &v));
}
/*

OPEN_MAX

FIRST INIT S[FD] && v.BUFFER

TOUJOURS COMPARER AVEC S[FD]

read while (ret != 0 && (v.i = charset >= 0))
{
	s[fd] = strjoin s[fd] + buffer
}
if (v.i != 0)
{
	line = substr(s[fd], 0, v.i, 0);
	tmp = substr(s[fd], v.i + 1, ft_strlen(s[fd]) - v.i + 1, 1)
	s[fd] = strdup(tmp);
}
else
	line = ft_strdup(s[fd]);
*/
int			main()
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	fd = open("capital", O_RDONLY);
	while ((i = get_next_line(fd, &line)))
	{
		//printf("gnl : %d, ", i);
		//ft_putendl(line);
	}
	close(fd);
	return(0);
}
