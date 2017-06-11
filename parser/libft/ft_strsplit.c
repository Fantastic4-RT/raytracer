/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:55:16 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 17:55:37 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}

static char	**last_resort(char **arr, int words)
{
	arr[words] = NULL;
	return (arr);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		start;
	int		length;
	int		count;

	i = 0;
	count = 0;
	if (s && (arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))))
	{
		while (s[i] != '\0')
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			length = i - start;
			if ((arr[count++] = ft_strnew(length)) && length != 0)
				while (length-- > 0)
					arr[count - 1][length] = s[start + length];
		}
		return (last_resort(arr, count_words(s, c)));
	}
	return (NULL);
}
