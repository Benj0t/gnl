/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:51:24 by bemoreau          #+#    #+#             */
/*   Updated: 2019/12/03 15:28:22 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

typedef struct		s_struct
{
	int				bool;
	int				ret;
	int				i;
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
	pt[i] = '\0';
	free(s1);
	free(s2);
	return (pt);
}

int		ft_charset(char *str, char charset)
{
	int i;

	if (!str)
		return(-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == charset)
			return(i);
		i++;
	}
	return (-1);
}

int		ft_good(char **line, t_struct *v, int fd)
{
	char *tmp;

	v->i = ft_charset(v->s[fd], '\n');
	free(*line);
	*line = ft_substr(v->s[fd], 0, v->i, 0);
	tmp = ft_strdup(v->s[fd]);
	v->s[fd] = ft_substr(tmp, v->i + 1, (ft_strlen(tmp) - (v->i)), 1);
	return(1);
}

int		ft_goodf(char **line, t_struct *v, int fd)
{
	if (*line)
		free(*line);
	*line = ft_substr(v->buffer, 0, v->i, 0);
	v->s[fd] = ft_substr(v->buffer, v->i + 1, (ft_strlen(v->buffer) - (v->i)), 1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	t_struct v;

	v.i = 0;
	if (!v.bool)
	{
		v.s[fd] = ft_strnew(BUFFER_SIZE);
		v.bool = 1;
	}
	if (v.s[fd] && ((v.i = ft_charset(v.s[fd], '\n')) >= 0))
		return (ft_good(line, &v, fd));
	if (!(v.buffer = ft_strnew(BUFFER_SIZE)))
		return (-1);
	if ((v.ret = read(fd, v.buffer, BUFFER_SIZE)) > 0)
	{
		if (v.s[fd])
		{
			v.tmp = ft_strjoin(v.s[fd], v.buffer);
			v.buffer = ft_strdup(v.tmp);
		}
		if ((v.i = ft_charset(v.buffer, '\n')) >= 0)
			return(ft_goodf(line, &v, fd));
		v.s[fd] = ft_strdup(v.buffer);
		get_next_line(fd, line);
	}
	else if (v.ret == 0 && ft_strlen(v.s[fd]) != 0)
	{
		free(*line);
		*line = ft_substr(v.s[fd], 0, (ft_strlen(v.s[fd])), 0);
		v.s[fd] = ft_substr(v.s[fd], v.i, ft_strlen(v.s[fd]), 1);
		if (ft_charset(v.s[fd], '\n') < 0)
			free(v.s[fd]);
		free(v.buffer);
		return(0);
	}
	else
		free(v.buffer);
	return ((v.ret == 0 && ft_charset(v.s[fd], '\n') < 0) ? 0 : 1);
}

void	ft_putendl(char *str)
{
	int i = 0;
	while (str[i])
		write(1, &(str[i++]), 1);
	write(1, "\n", 1);
}

int			main()
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	fd = open("test", O_RDONLY);
	while ((i = get_next_line(fd, &line)))
	{
		//printf("gnl : %d, ", i);
		ft_putendl(line);
	}
	close(fd);
	while (1);
	return(0);
}
