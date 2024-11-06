/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoll.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 15:48:06 by skoene        #+#    #+#                 */
/*   Updated: 2024/10/11 15:52:02 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace23(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_isspace23(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result < 0 && sign == 1)
			return (LLONG_MAX);
		else if (result < 0 && sign == -1)
			return (LLONG_MIN);
		str++;
	}
	return (sign * result);
}
