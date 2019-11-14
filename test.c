int		ft_charset(char *str, char *charset)
{
	int i;
    int j;

	i = -1;
	while (str[++i])
    {
        j = 0;
		while  (charset[j])
            if (str[i] == charset[j++])
			    return (i);
    }
    return (-1);
}

int main()
{
    char *str = "Bonsoir\n a tous";
    char *c = "\n\0";
    printf("%d", ft_charset(str, c));
}