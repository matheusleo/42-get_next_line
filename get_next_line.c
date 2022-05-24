/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:27 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/24 12:06:50 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*mount_line(char *line, char *to_append)
{
	size_t	index;
	size_t	length_str;
	char	*splitted_str;
	char	*new_line;

	index = 0;
	// análise kowalski - e se line já tiver um '\n'?
	length_str = (ft_strchr(to_append, '\n') + 1) - to_append;
	splitted_str = (char *)malloc(sizeof(char) * length_str);
	if (!splitted_str)
		return (NULL);
	while (index < length_str)
	{
		splitted_str[index] = to_append[index];
		if (ft_strchr(splitted_str, '\n'))
			break;
		index++;
	}
	new_line = ft_strjoin(line, splitted_str);
	free(splitted_str);
	return (new_line);
}

char	*get_line(int fd)
{
	static char	*buffer;
	ssize_t		char_read;
	char		*line;

	if (buffer == NULL)
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		line = ft_strdup("");
	}
	else
		line = ft_strdup(ft_strchr(buffer, '\n') + 1);
	char_read = read(fd, buffer, BUFFER_SIZE);
	while (char_read > 0)
	{
		if (ft_strchr(buffer, '\n'))
		{
			line = mount_line(line, buffer);
			return (line);
		}
		line = ft_strjoin(line, buffer);
		char_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(line);
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
