/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:51:24 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/18 18:38:18 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int		ft_free(char **line, t_struct *v, int fd)
{
	if (v->tmp)
		free(v->tmp);
	if (v->s[fd])
		free(v->s[fd]);
	if (v->buffer)
		free(v->buffer);
	if (*line)
		free(*line);
	v->tmp = NULL;
	v->s[fd] = NULL;
	v->buffer = NULL;
	line = NULL;
	return (-1);
}

static int		ft_charset(char *str)
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

static int		ft_ret(t_struct *v, char **line, int fd, int bool)
{
	v->pos = ft_charset(v->s[fd]);
	v->len = ft_strlen(v->s[fd]);
	if (bool == 0)
	{
		*line = ft_strdup(v->s[fd], v->len);
		v->s[fd] = NULL;
		return (0);
	}
	if (bool == 1 || bool == 2)
	{
		v->len = v->len - v->pos;
		if (!(*line = ft_substr(v->s[fd], 0, v->pos, 0)))
			return (ft_free(line, v, fd));
		if (!(v->tmp = ft_substr(v->s[fd], v->pos + 1, v->len, 1)))
			return (ft_free(line, v, fd));
		if (bool == 2 && !(v->s[fd] = ft_strdup(v->tmp, v->len)))
			return (ft_free(line, v, fd));
		if (bool == 1 && !(v->s[fd] = ft_strdup(v->tmp, v->len)))
			return (ft_free(line, v, fd));
		return (1);
	}
	return (-1);
}

static int		my_gnl(int fd, char **line, t_struct *v)
{
	while ((v->ret = read(fd, v->buffer, BUFFER_SIZE)) > 0 &&
			(v->pos = ft_charset(v->s[fd])) < 0)
	{
		v->buffer[v->ret] = '\0';
		v->len += v->ret;
		if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer, v->len)))
			return (ft_free(line, v, fd));
		if (!(v->s[fd] = ft_strdup(v->tmp, v->len)))
			return (ft_free(line, v, fd));
	}
	v->len += v->ret;
	v->buffer[v->ret] = '\0';
	if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer, v->len)))
		return (ft_free(line, v, fd));
	if (!(v->s[fd] = ft_strdup(v->tmp, v->len)))
		return (ft_free(line, v, fd));
	v->pos = ft_charset(v->s[fd]);
	free(v->buffer);
	v->buffer = NULL;
	if (v->pos >= 0)
		return (ft_ret(v, line, fd, 2));
	else if (v->ret == 0)
		return (ft_ret(v, line, fd, 0));
	return (ft_free(line, v, fd));
}

int				get_next_line(int fd, char **line)
{
	static t_struct v;

	if (line == NULL || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (!v.s[fd])
		if (!(v.s[fd] = ft_calloc(0, 0)))
			return (ft_free(line, &v, fd));
	if (!(v.buffer = ft_calloc(1, BUFFER_SIZE + 1)))
		return (ft_free(line, &v, fd));
	v.len = ft_strlen(v.s[fd]);
	if ((v.pos = ft_charset(v.s[fd])) >= 0)
	{
		free(v.buffer);
		v.buffer = NULL;
		return (ft_ret(&v, line, fd, 1));
	}
	return (my_gnl(fd, line, &v));
}
