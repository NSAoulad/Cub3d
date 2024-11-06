/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 15:15:12 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/06 17:39:14 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	src_len;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

char	*ft_strdup_g(char *s)
{
	char	*str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, size);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	char	*str;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, (ft_strlen(s1) + 1));
	ft_strlcpy(&str[ft_strlen(s1)], s2, (ft_strlen(s2) + 1));
	return (str);
}

int	ft_strncmp(const char *str, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == str2[i] && (str[i] && str2[i]))
		{
			i++;
		}
		else
		{
			return ((unsigned char)str[i] - (unsigned char)str2[i]);
		}
	}
	return (0);
}
