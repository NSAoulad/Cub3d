/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 14:18:23 by skoene        #+#    #+#                 */
/*   Updated: 2023/11/01 12:18:53 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	while (n--)
	{
		if (*us1 != *us2)
			return ((int)(*us1 - *us2));
		us1++;
		us2++;
	}
	return (0);
}
