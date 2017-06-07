/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:08:05 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/02 15:08:11 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_lst;
	size_t	content_size_new;
	size_t	i;
	void	*content_new;

	i = 0;
	new_lst = NULL;
	if ((new_lst = (t_list *)malloc(sizeof(t_list))) && content_size)
	{
		content_size_new = content_size;
		if (content == NULL)
		{
			new_lst->content = NULL;
			new_lst->content_size = 0;
		}
		else if ((content_new = malloc(content_size_new)) && content)
		{
			while (i++ < content_size)
				((char *)content_new)[i - 1] = ((char *)content)[i - 1];
			new_lst->content = content_new;
			new_lst->content_size = content_size_new;
			new_lst->next = NULL;
		}
	}
	return (new_lst);
}
