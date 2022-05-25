/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:27 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/24 22:38:25 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

char	*create_line(char *line, char *to_append)
{
	size_t	index;
	size_t	len_to_append;
	char	*new_str;
	char	*new_line;

	index = 0;
	if (ft_strchr(to_append, '\n'))
		len_to_append = ft_strchr(to_append, '\n') - to_append;
	else
		len_to_append = ft_strlen(to_append);
	new_str = (char *)malloc(sizeof(char) * len_to_append);
	while (index <= len_to_append)
	{
		new_str[index] = to_append[index];
		index++;
	}
	new_line = ft_strjoin(line, new_str);
	return (new_line);
}

char	*get_line(int fd)
{
	char	*line = "";
	ssize_t		nb_read;
	char		*temp;

	temp = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!temp)
		return (NULL);
	nb_read = read(fd, temp, BUFFER_SIZE);
	while (nb_read > 0)
	{
		if (ft_strchr(temp, '\n'))
		{
			line = create_line(line, temp);
			free(temp);
			return (line);
		}
		line = create_line(line, temp);
		nb_read = read(fd, temp, BUFFER_SIZE);
	}
	free(temp);
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
