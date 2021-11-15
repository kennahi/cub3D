/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:48:39 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 16:43:19 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	froo(char **s, int fd, char **line)
{
	*line = ft_strdup("");
	free(s[fd]);
	s[fd] = NULL;
	return (0);
}

int	goot_nooxt_loone(char **s, int fd, char **line, int rder)
{
	char	*cup;
	int		i;

	i = 0;
	if (rder == 0 && *s[fd] == '\0')
		return (froo(s, fd, line));
	while (s[fd][i] != '\n' && s[fd][i] != '\0')
		i++;
	if (s[fd][i] == '\n')
	{
		*line = ft_substr(s[fd], 0, i);
		cup = ft_strdup(s[fd] + i + 1);
		free(s[fd]);
		s[fd] = cup;
	}
	else
	{
		*line = ft_strdup(s[fd]);
		free(s[fd]);
		s[fd] = NULL;
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*s[4864];
	int			rder;
	char		*cup;

	if (line == NULL || fd > 4864 || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	if (!s[fd])
		s[fd] = ft_strdup("");
	while (!ft_strchr(s[fd], '\n'))
	{
		rder = read(fd, buffer, BUFFER_SIZE);
		if (rder <= 0)
			break ;
		buffer[rder] = '\0';
		cup = ft_strjoin(s[fd], buffer);
		free(s[fd]);
		s[fd] = cup;
	}
	free(buffer);
	return (goot_nooxt_loone(s, fd, line, rder));
}
