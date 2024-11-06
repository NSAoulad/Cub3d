/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 18:13:26 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/06 17:37:37 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	jstr = (char *)malloc(i + j + 1);
	if (!jstr)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		jstr[j] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j])
	{
		jstr[i + j] = s2[j];
		j++;
	}
	jstr[i + j] = '\0';
	return (jstr);
}
