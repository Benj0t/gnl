/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:57:49 by bemoreau          #+#    #+#             */
/*   Updated: 2019/11/21 16:44:04 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_struct
{
	int				ret;
	int				i;
	char 			*buffer;
}					t_struct;


size_t	ft_strlen(char *str);
char	*ft_freedup(char *src);
char	*ft_strnew(unsigned int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_freejoin(char **s1, char **s2);
int		ft_charset(char *str, char charset);
int		ft_fill_good(char **s, int i, char **line);
int		ft_fill_bad(char **s, int i, char **line, char **buffer);
int		get_next_line(int fd, char **line);
void	ft_save(char **line, char **s, int i, char **buffer);

#endif
