/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:17:09 by skoene        #+#    #+#                 */
/*   Updated: 2023/11/04 20:33:23 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isdelimiter(char c, char delimiter)
{
	return (c == delimiter);
}

static size_t	ft_countword(char const *s, char delimiter)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		{
			if (!ft_isdelimiter(*s, delimiter))
			{
				word_count++;
				while (*s && !ft_isdelimiter(*s, delimiter))
					s++;
			}
			else
				s++;
		}
	}
	return (word_count);
}

static int	ft_free(char **result, size_t n)
{
	while (n > 0)
		free(result[--n]);
	free(result);
	return (1);
}

static char	**ft_create_substring(char const *s, char c, char **result)
{
	size_t		i;
	const char	*start;

	result = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_isdelimiter(*s, c))
			s++;
		if (*s)
		{
			start = s;
			while (*s && !ft_isdelimiter(*s, c))
				s++;
			result[i] = ft_substr(start, 0, (size_t)(s - start));
			if (!result[i] && ft_free(result, i) == 1)
				return (NULL);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = NULL;
	result = ft_create_substring(s, c, result);
	return (result);
}
