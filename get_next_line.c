/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:27 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/31 09:46:48 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

char	*check_remain(char *remain)
{
	char	*current_line;
	// ssize_t	line_len;
	// ssize_t	index;

	// index = -1;
	//if remain's has not content
	if (!remain)
		return (NULL);
	//if remain's content can be returned
	// if (ft_strchr(remain, '\n'))
	// {
	// 	line_len = ft_strchr(remain, '\n') - remain + 2;
	// 	current_line = (char *)malloc(sizeof(char) * line_len);
	// 	if (!current_line)
	// 		return (NULL);
	// 	while (++index < line_len - 1)
	// 		current_line[index] = remain[index];
	// 	current_line[index] = '\0';
	// 	return (current_line);
	// }
	// //if remain's content cannot be returned
	current_line = ft_strdup(remain);
	return (current_line);

}

char	*compute_line(char *line_raw)
{
	ssize_t	line_len;
	char	*line;
	ssize_t	index;

	if (ft_strchr(line_raw, '\n'))
		// create the computed line from start to the first '\n'
		line_len = (ft_strchr(line_raw, '\n') + 1) - line_raw + 1;
	else
		// OR create the computed line from start to the final
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
	// printf("line - %s\n", line);
	return (line);
}

char	*get_remain(char *line_raw)
{
	char	*remain;

	if (ft_strchr(line_raw, '\n'))
		remain = ft_strdup(ft_strchr(line_raw, '\n') + 1);
	else
		remain = NULL;
	free(line_raw);
	return(remain);
}

char	*create_line(char **current_line, int fd)
{
	char	*aux;
	ssize_t	nb_read;
	char	temp[BUFFER_SIZE + 1];
	// 1. current_line has content
	//	1.1 current_line == content that can be returned
	/*
		need to compute the line from the start to the first '\n'
		save the current_line content in the current_line variable
		return the current_line
	*/
	if (*current_line && ft_strchr(*current_line, '\n'))
	{
		aux = ft_strdup(*current_line);
		// printf("\n> aux - {%s}", aux);
		*current_line = compute_line(aux);
		return (get_remain(aux));
	}
	//	1.2 current_line == content that cannot be returned now
	/*
		need to read the file (l. 108)
		save the info from the reading (l. 108-111)
		mount the new line using the content of \
		current_line and form the read file (l. 112-113)
		verify again if it can be returned (step 2)
	*/
	nb_read = read(fd, temp, BUFFER_SIZE);
	if (nb_read <= 0)
		return (NULL);
	printf("nb_read - %ld", nb_read);
	while (nb_read > 0)
	{
		// printf("\nnb_read - %ld\n", nb_read);
		temp[nb_read] = '\0';
		if (*current_line)
		{
			aux = ft_strdup(*current_line);
			free(*current_line);
		}
		else
			aux = ft_strdup("");
		*current_line = ft_strjoin(aux, temp);
		free(aux);
		if (*current_line && ft_strchr(*current_line, '\n'))
		{
			aux = ft_strdup(*current_line);
			free(*current_line);
			*current_line = compute_line(aux);
			return (get_remain(aux));
		}
		nb_read = read(fd, temp, BUFFER_SIZE);
	}
	return (NULL);
	//2. current_line == NULL
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// printf("remain - {%s}\n", remain);
	current_line = check_remain(remain);
	// printf("current_line - {%s}", current_line);
	free(remain);
	/*
		problem with current_line:
		it's returning the line + the remain
	*/
	remain = create_line(&current_line, fd);
	printf("current_line {%s}\n", current_line);
	if (!remain)
		free(remain);
	/* @create_line should return the excess of current_line
		return the excess to remain after creating the line */
	// printf(" > current_line - {%s}\n", current_line);
	return (current_line);
}
