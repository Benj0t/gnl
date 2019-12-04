#include "get_next_line.h"

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