/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/28 14:08:35 by skoene        #+#    #+#                 */
/*   Updated: 2023/11/04 12:12:17 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*store_next;

	if (!lst)
		return ;
	while (*lst)
	{
		store_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = store_next;
	}
}
