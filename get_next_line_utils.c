/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/05/24 21:44:21 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((char)*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static int	join(char *to, const char *from, size_t to_start)
{
	while (*from)
	{
		to[to_start] = *from++;
		to_start++;
	}
	return (to_start);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len_new_str;
	size_t	index;

	len_new_str = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(sizeof(char) * (len_new_str));
	if (!new_str)
		return (NULL);
	index = 0;
	index = join(new_str, s1, index);
	index = join(new_str, s2, index);
	new_str[index] = '\0';
	return (new_str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	s_index;
	size_t	d_index;

	s_len = ft_strlen(src);
	d_index = ft_strlen(dst);
	s_index = 0;
	if (d_index >= size)
		return (s_len + size);
	while (s_index + d_index + 1 < size && src[s_index])
	{
		dst[d_index + s_index] = src[s_index];
		s_index++;
	}
	dst[d_index + s_index] = '\0';
	return (d_index + s_len);
}
