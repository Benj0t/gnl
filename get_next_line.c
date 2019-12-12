/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:51:24 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/12 13:52:44 by marvin           ###   ########.fr       */
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

	if (!line || fd < 0 || BUFFER_SIZE <= 0 || !(v.buffer = ft_strnew(BUFFER_SIZE)))
		return (ft_free(line));
	if (!v.bool)
		if (!(v.s[fd] = ft_strnew(NULL)))
			return (ft_free(line));
	v.bool = 1;
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

void ft_putendl(unsigned char *str)
{
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
	}
	write(1, "\n", 1);
}

int			main()
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	fd = open("germaine", O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		ft_putendl((unsigned char *)line);
		free(line);
		//printf("%d\n", i);
	}
	ft_putendl((unsigned char *)line);
	//printf("%d\n", i);
	free(line);
	close(fd);
	return (0);
}
