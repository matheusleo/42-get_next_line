/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:27 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/31 22:24:03 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*compute_line(char *line_raw)
{
	ssize_t	line_len;
	char	*line;
	ssize_t	index;

	if (ft_strchr(line_raw, '\n'))
		line_len = (ft_strchr(line_raw, '\n') + 1) - line_raw + 1;
	else
		line_len = ft_strlen(line_raw) + 1;
	line = (char *)malloc(sizeof(char) * line_len);
	if (!line)
		return (NULL);
	index = 0;
	while (index < line_len - 1)
	{
		line[index] = line_raw[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

char	*get_remain(char *line_raw)
{
	char	*remain;

	if (line_raw && ft_strchr(line_raw, '\n') + 1)
		remain = ft_strdup(ft_strchr(line_raw, '\n') + 1);
	else
		remain = NULL;
	free(line_raw);
	return (remain);
}

char	*mount_line(char **line_raw)
{
	char	*aux;

	aux = ft_strdup(*line_raw);
	free(*line_raw);
	*line_raw = compute_line(aux);
	return (get_remain(aux));
}

char	*create_line(char **current_line, int fd)
{
	char	*aux;
	ssize_t	nb_read;
	char	temp[BUFFER_SIZE + 1];

	if (*current_line && ft_strchr(*current_line, '\n'))
		return (mount_line(current_line));
	nb_read = read(fd, temp, BUFFER_SIZE);
	if (nb_read <= 0)
		return (NULL);
	while (nb_read > 0)
	{
		temp[nb_read] = '\0';
		if (*current_line)
			aux = ft_strdup(*current_line);
		else
			aux = ft_strdup("");
		free(*current_line);
		*current_line = ft_strjoin(aux, temp);
		free(aux);
		if (*current_line && ft_strchr(*current_line, '\n'))
			return (mount_line(current_line));
		nb_read = read(fd, temp, BUFFER_SIZE);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain || ft_strlen(remain) == 0)
		current_line = NULL;
	else
		current_line = ft_strdup(remain);
	free(remain);
	remain = create_line(&current_line, fd);
	if (!remain)
		free(remain);
	return (current_line);
}
