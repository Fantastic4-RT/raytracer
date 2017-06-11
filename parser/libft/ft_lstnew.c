/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 19:19:25 by atrepyto          #+#    #+#             */
/*   Updated: 2016/12/03 16:21:09 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *fresh;

	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
		return (NULL);
	if (!content)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
	}
	else
	{
		fresh->content_size = content_size;
		fresh->content = ft_memalloc(fresh->content_size);
		if (!fresh->content)
			return (NULL);
		fresh->content = ft_memcpy(fresh->content, content,
				fresh->content_size + 1);
		((char *)(fresh->content))[fresh->content_size] = '\0';
	}
	fresh->next = NULL;
	return (fresh);
}
