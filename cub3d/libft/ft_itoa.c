/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:43:19 by skoene        #+#    #+#                 */
/*   Updated: 2023/11/01 12:21:42 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int nb, int count)
{
	if (nb < 0)
	{
		count++;
		nb = nb * -1;
	}
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

static char	*ft_result(int i, int nb, char *result)
{
	while (nb > 0)
	{
		result[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		i;
	int		nb;
	int		count;
	char	*result;

	nb = n;
	count = 0;
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb == INT_MIN)
		return (ft_strdup("-2147483648"));
	count = ft_count(nb, count);
	result = (char *)malloc(count + 1);
	if (!result)
		return (NULL);
	result[count] = '\0';
	nb = n;
	if (nb < 0)
	{
		result[0] = '-';
		nb = nb * -1;
	}
	i = count - 1;
	ft_result(i, nb, result);
	return (result);
}
