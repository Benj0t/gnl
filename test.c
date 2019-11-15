#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return(i);
}

char	*ft_strdup(char **src)
{
	char	*str;
	int		i;

	i = 0;
	while ((*src)[i])
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while ((*src)[++i])
		str[i] = (*src)[i];
	str[i] = '\0';
    if (*src)
        free(*src);
	return (str);
}



char *ft_strnew(int nb)
{
    char *str;

    if (!(str = (char *)malloc(sizeof(char) * (nb + 1))))
        return (NULL);
    str[nb] = '\0';
    return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i + 1 <= len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char **s1, char *s2)
{
	char	*pt;
	int		i;
	int		j;

	if ((!*s1 || !s2) ||
		(!(pt = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	i = 0;
	j = 0;
	while ((*s1)[j])
	{
		pt[i] = (*s1)[j];
		++i;
		++j;
	}
	j = 0;
	while (s2[j])
	{
		pt[i] = s2[j];
		++i;
		++j;
	}
	pt[i] = '\0';
    free(*s1);
	return (pt);
}

int		ft_charset(char *str, char charset)
{
	int i;
    int j;

	i = -1;
	while (str[++i])
        if (str[i] == charset)
        {
            return (i);
        }
    return (-1);
}

int     ft_fill_good(char **s, int i, char **line, char **buffer)
{          
    *line = ft_substr(*s, 0, i);
    *s = ft_substr(*s, i + 1, (ft_strlen(*s)));
    return (1);
}

int     ft_fill_bad(char **s, int i, char **line, char **buffer)
{ 
    *line = ft_substr(*buffer, 0, i);
    *s = ft_substr(*buffer, i + 1, (ft_strlen(*buffer)));
    return (0);
}

int     ft_save(char **line, char **s, int i)
{
    *line = ft_substr(*s, 0, ft_strlen(*s));
    *s = ft_substr(*s, i + 1, (ft_strlen(*s)));
}

int     get_next_line(int fd, char **line)
{
    static char *s[4096];
    char *buffer;
    int ret;
    int i;

    if (ft_strlen(s[fd]) > 0 && (i = ft_charset(s[fd], '\n'))> 0)
        return (ft_fill_good(&(s[fd]), i, line, &buffer));
    if (!(buffer = ft_strnew(BUFFER_SIZE)))
        return (-1);
    if ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (ft_strlen(s[fd]))
            buffer = ft_strjoin(&(s[fd]), buffer);
        if ((i = ft_charset(buffer, '\n')) > 0)
            return (ft_fill_bad(&(s[fd]), i, line, &buffer));
        else
        {
            s[fd] = ft_strdup(&buffer);
            get_next_line(fd, line);
        }
    }
    else if (ret == 0 && ft_strlen(s[fd]) != 0)
        ft_save(line, &(s[fd]), i);
    return ((ret == 0) ? 0 : -1);
}

int main()
{
    char *line;
    int fd = open("test", O_RDONLY);
    get_next_line(fd, &line);
    printf("%s\n",line);
    get_next_line(fd, &line);
    printf("%s\n", line);
    get_next_line(fd, &line);
    printf("%s\n", line);
    get_next_line(fd, &line);
    printf("%s\n", line);
    get_next_line(fd, &line);
    printf("%s\n", line);
    get_next_line(fd, &line);
    printf("%s\n", line);
    get_next_line(fd, &line);
    printf("%s\n", line);
}