/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:51:24 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/12 18:58:11 by bemoreau         ###   ########.fr       */
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

int my_gnl(int fd, char **line, t_struct *v)
{
	while ((v->ret = read(fd, v->buffer, BUFFER_SIZE)) > 0 && (v->pos = ft_charset(v->s[fd])) < 0)
	{
		v->buffer[v->ret] = '\0';
		if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer)) || !(v->s[fd] = ft_strdup(v->tmp)) || !(v->buffer = ft_strnew(BUFFER_SIZE)))
			return (ft_free(line));
	}
	v->buffer[v->ret] = '\0';
	if (!(v->tmp = ft_strjoin(v->s[fd], v->buffer)) || !(v->s[fd] = ft_strdup(v->tmp)) || !(v->buffer = ft_strnew(BUFFER_SIZE)))
			return (ft_free(line));
	free(v->buffer);
	v->pos = ft_charset(v->s[fd]);
	if (v->pos >= 0)
	{
		if (!(*line = ft_substr(v->s[fd], 0, v->pos, 0)) || !(v->tmp = ft_substr(v->s[fd], v->pos + 1, ft_strlen(v->s[fd]), 1)) || !(v->s[fd] = ft_strdup(v->tmp)))
			return (ft_free(line));
		return (1);
	}
	else if (v->ret == 0)
		return ((*line = ft_strdup(v->s[fd])) ? 0 : -1);
	else
		return (ft_free(line));
}

int		get_next_line(int fd, char **line)
{
	static t_struct v;

	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0 || !(v.buffer = ft_strnew(BUFFER_SIZE)))
		return ((line == NULL) ? -1 : ft_free(line));
	v.bool[fd] += 1;
	if (!v.s[fd])
	{
		if (!(v.s[fd] = ft_strnew(0)))
			return (ft_free(line));
		v.fd = fd;
	}
	if ((v.pos = ft_charset(v.s[fd])) >= 0)
	{
		if (!(*line = ft_substr(v.s[fd], 0, v.pos, 0)) || !(v.tmp = ft_substr(v.s[fd], v.pos + 1, ft_strlen(v.s[fd]), 1)))
			return (ft_free(line));
		free(v.buffer);
		return ((v.s[fd] = ft_strdup(v.tmp)) ? 1 : ft_free(line));
	}
	if (v.ret == 0 && ft_strlen(v.s[fd]) != 0 && v.pos == -1)
		return ((*line = ft_strdup(v.s[fd])) ? 0 : ft_free(line));
	return (my_gnl(fd, line, &v));
}