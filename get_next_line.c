#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return(i);
}

char	*ft_strdup(const char *src)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	int		i;
	int		j;

	if ((!s1 || !s2) ||
		(!(pt = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		pt[i] = s1[j];
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
            return(i);
        }
    return (-1);
}

int     get_next_line(int fd, char **line)
{
    int BUFFER_SIZE = 1025;
    static char *s[4096];
    char *buffer;
    int ret;
    int i;

    i = 0;
    // VERIFIER SI PRESENCE DE \N DANS LE STATIC
    // COMBATTRE LE \0
    if (!(buffer = ft_strnew(BUFFER_SIZE)))
        return (-1);
    if ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (ft_strlen(s[fd]))
        {
            buffer = ft_strjoin(s[fd], buffer);
            free(s[fd]);
        }
        if ((i = ft_charset(buffer, '\n')) > 0)
        {
            
            *line = ft_substr(buffer, 0, i);
            s[fd] = ft_substr(buffer, i + 1, (ft_strlen(buffer)));
            return(1);
        }
        else
        {
            s[fd] = ft_strdup(buffer);
            free(buffer);
            get_next_line(fd, line);
        }
    }
    else
        return((ret == 0) ? 0 : -1);
}

int main()
{
    char *line;
    int fd = open("test", O_RDONLY);
    printf("\n%d", get_next_line(fd, &line));
    printf("\n%s",line);
    printf("\n%d", get_next_line(fd, &line));
    printf("\n%s", line);
    printf("\n%d", get_next_line(fd, &line));
    printf("\n%s", line);
}