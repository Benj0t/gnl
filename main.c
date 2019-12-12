#include "get_next_line.h"

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
	fd = open("42TESTERS-GNL/files/empty_lines", O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		ft_putendl((unsigned char *)line);
		free(line);
		//printf("%d\n", i);
	}
	ft_putendl((unsigned char *)line);
	//printf("%d\n", i);
	free(line);
	//close(fd);
	fd = open("42TESTERS-GNL/files/alphabet", O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		ft_putendl((unsigned char *)line);
		free(line);
		//printf("%d\n", i);
	}
	//system("leaks a.out");
	return (0);
}
