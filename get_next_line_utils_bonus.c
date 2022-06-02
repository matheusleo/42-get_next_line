/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:50:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/06/01 22:37:02 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
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

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*dest;
	int		d_len;

	d_len = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dest)
	{
		while (d_len <= s_len)
		{
			dest[d_len] = s[d_len];
			d_len++;
		}
		return (dest);
	}
	return (NULL);
}
