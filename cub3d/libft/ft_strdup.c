/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 16:19:40 by skoene        #+#    #+#                 */
/*   Updated: 2024/09/10 18:13:33 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	j;
	char	*s2;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (NULL);
	while (s[j])
	{
		s2[j] = s[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
