/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:40:32 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/02 16:40:41 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next_l;

	if (*alst)
	{
		while ((*alst))
		{
			next_l = (*alst)->next;
			(*del)((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = next_l;
		}
	}
}
