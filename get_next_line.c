/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:27 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/28 13:55:24 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

static char	*compute_line(char *line)
{
	size_t	index;
	char	*new_line;
	size_t	line_len;

	index = 0;
	if (ft_strchr(line, '\n'))
		line_len = (ft_strchr(line, '\n') + 1) - line + 1;
	else
		line_len = ft_strlen(line) + 1;
	new_line = (char *)malloc(sizeof(char) * line_len);
	if (!new_line)
		return (NULL);
	while (index < line_len - 1)
	{
		new_line[index] = line[index];
		index++;
	}
	new_line[index] = '\0';
	return (new_line);
}

static char	*get_line(int fd)
{
	static char	*line;
	char	*new_line;
	char	temp[BUFFER_SIZE + 1];
	ssize_t	nb_read;
	char	*previous_line;

	if (line != NULL && ft_strchr(line, '\n'))
	{
		new_line = compute_line(line);
		previous_line = ft_strdup(line);
		if (ft_strchr(previous_line, '\n') + 1)
			line = ft_strchr(previous_line, '\n') + 1;
		else
			free(line);
		free(previous_line);
		return (new_line);
	}
	nb_read = read(fd, temp, BUFFER_SIZE);
	while (nb_read > 0)
	{
		temp[nb_read] = '\0';
		previous_line = ft_strdup(line);
		line = ft_strjoin(previous_line, temp);
		previous_line = ft_strdup(line);
		if (ft_strchr(line, '\n'))
		{
			new_line = compute_line(line);
			if (ft_strchr(previous_line, '\n') + 1)
				line = ft_strchr(previous_line, '\n') + 1;
			else
				free(line);
			free(previous_line);
			return (new_line);
		}
		nb_read = read(fd, temp, BUFFER_SIZE);
	}
	if (*line)
	{
		new_line = compute_line(line);
		free(line);
		return (new_line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_line = get_line(fd);
	return (current_line);
}
