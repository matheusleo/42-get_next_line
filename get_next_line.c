/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:27 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/26 23:15:13 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

char	*compute_line(char *line)
{
	size_t	index;
	char	*new_line;
	size_t	line_len;

	index = 0;
	line_len = ft_strchr(line, '\n') - line + 2;
	new_line = (char *)malloc(sizeof(char) * line_len);
	if (!new_line)
		return (NULL);
	while (index < line_len)
	{
		new_line[index] = line[index];
		index++;
	}
	return (new_line);
}

char	*get_line(int fd)
{
	static char	*line = "";
	char	*new_line;
	char	temp[BUFFER_SIZE];
	ssize_t	nb_read;

	if (ft_strchr(line, '\n'))
	{
		new_line = compute_line(line);
		if (!(ft_strchr(line, '\n') + 1))
			line = "";
		else
			line = ft_strchr(line, '\n') + 1;
		return (new_line);
	}
	nb_read = read(fd, temp, BUFFER_SIZE);
	while (nb_read > 0)
	{
		line = ft_strjoin(line, temp);
		if (ft_strchr(line, '\n'))
		{
			new_line = compute_line(line);
			if (!(ft_strchr(line, '\n') + 1))
				line = "";
			else
				line = ft_strchr(line, '\n') + 1;
			return (new_line);
		}
		nb_read = read(fd, temp, BUFFER_SIZE);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = get_line(fd);
	return (next_line);
}
