/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 20:31:42 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/02 20:31:50 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;

	start = NULL;
	new = NULL;
	if (lst)
	{
		new = (*f)(lst);
		start = new;
		while (lst->next)
		{
			new->next = (*f)(lst->next);
			new = new->next;
			lst = lst->next;
		}
	}
	return (start);
}
