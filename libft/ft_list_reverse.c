/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:29:40 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/03 17:29:47 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list *previous;
	t_list *next;
	t_list *current;

	previous = NULL;
	current = *begin_list;
	while (current != 0)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*begin_list = previous;
}
