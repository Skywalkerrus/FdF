/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:32:56 by bantario          #+#    #+#             */
/*   Updated: 2019/05/27 18:30:20 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void		*ft_memchrr(char *s, int c, size_t j)
{
	size_t	i;

	i = 0;
	while (i <= j && ((char*)s)[i] != '\0')
	{
		if (((char*)s)[i] == (char)c)
		{
			((char*)s)[i] = '\0';
			return (&((char*)s)[i + 1]);
		}
		i++;
	}
	return (NULL);
}

static void		my_free(char *mas)
{
	if (mas)
		free(mas);
	return ;
}

static int		ft_search_union(char **m3, char *m2, int fd, char **line)
{
	int					fdr;
	char				*mas;
	char				*del;
	int					re;

	mas = ft_strnew(BUFF_SIZE);
	fdr = 1;
	while (m2 == NULL && (fdr = read(fd, mas, BUFF_SIZE)) > 0)
	{
		mas[fdr] = '\0';
		m2 = ft_memchrr(mas, '\n', BUFF_SIZE);
		del = *line;
		*line = ft_strjoin(*line, mas);
		my_free(del);
		re = fdr;
	}
	del = m3[fd];
	m3[fd] = ft_strjoin(m3[fd], m2);
	my_free(del);
	if (fdr > 0 || re > 0 || *line[0])
		fdr = 1;
	my_free(mas);
	return (fdr);
}

static int		ft_union(char **line, char **mas3, char *mas2)
{
	char *del;

	del = *line;
	*line = ft_strjoin(*line, *mas3);
	my_free(del);
	del = *mas3;
	*mas3 = ft_strdup(mas2);
	my_free(del);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*mas2;
	static char		*mas3[GO];
	char			*del;

	if (line == NULL || fd < 0 ||
			BUFF_SIZE < 0 || read(fd, &mas2, 0) < 0)
		return (-1);
	*line = ft_strnew(0);
	mas2 = NULL;
	if (mas3[fd])
	{
		if ((mas2 = ft_memchrr(mas3[fd], '\n', BUFF_SIZE)))
			return (ft_union(line, mas3 + fd, mas2));
		del = *line;
		*line = ft_strjoin(*line, mas3[fd]);
		my_free(del);
		my_free(mas3[fd]);
		mas3[fd] = NULL;
	}
	if (!mas3[fd])
		mas3[fd] = ft_strnew(0);
	return (ft_search_union(mas3, mas2, fd, line));
}
