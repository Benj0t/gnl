/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:51:24 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/13 07:28:56 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_free(char **line)
{
	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = '\0';
	return (-1);
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

int		ft_ret(t_struct *v, char **line, int fd, int bool)
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
			return (ft_free(line));
		if (!(v->tmp = ft_substr(v->s[fd], v->pos + 1, v->len, 1)))
			return (ft_free(line));
		if (bool == 2)
			if (!(v->s[fd] = ft_strdup(v->tmp, v->len)))
				return (ft_free(line));
		if (bool == 1)
			if (!(v->s[fd] = ft_strdup(v->tmp, v->len)))
				return (ft_free(line));
		return (1);
	}
	return (-1);
}

int		my_gnl(int fd, char **line, t_struct *v)
{
	while ((v->ret = read(fd, v->buffer, BUFFER_SIZE)) > 0 &&
			(v->pos = ft_charset(v->s[fd])) < 0)
	{
		v->buffer[v->ret] = '\0';
		v->len += v->ret;
		if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer, v->len)))
			return (ft_free(line));
		if (!(v->s[fd] = ft_strdup(v->tmp, v->len)))
			return (ft_free(line));
	}
	v->len += v->ret;
	v->buffer[v->ret] = '\0';
	if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer, v->len)))
		return (ft_free(line));
	if (!(v->s[fd] = ft_strdup(v->tmp, v->len)))
		return (ft_free(line));
	free(v->buffer);
	v->pos = ft_charset(v->s[fd]);
	if (v->pos >= 0)
		return (ft_ret(v, line, fd, 2));
	else if (v->ret == 0)
		return (ft_ret(v, line, fd, 0));
	return (ft_free(line));
}

int		get_next_line(int fd, char **line)
{
	static t_struct v;

	if (line == NULL || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (!(v.buffer = ft_calloc(1, BUFFER_SIZE + 1)))
		return (ft_free(line));
	if (!v.s[fd])
		if (!(v.s[fd] = ft_calloc(1, 0)))
			return (ft_free(line));
	v.len = ft_strlen(v.s[fd]);
	if ((v.pos = ft_charset(v.s[fd])) >= 0)
	{
		free(v.buffer);
		return (ft_ret(&v, line, fd, 1));
	}
	return (my_gnl(fd, line, &v));
}
