/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:54:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/09 21:16:23 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	words_counter(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static char	*create_word(const char *s, int len)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((sizeof(char)) * (len + 1));
	if (!ptr)
		return (NULL); 
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	**free_prev(char **s, int end)
{
	int	i;

	i = 0;
	while (end - i >= 0)
	{
		free(s[end - i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**fill_in(const char *s, char c, int count, char **arr)
{
	int		j;
	int		w;

	w = -1;
	while (++w < count)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (*(s + j) && *(s + j) != c)
			j++;
		arr[w] = create_word(s, j);
		if (!arr[w])
			return (free_prev(arr, w));
		while (*s && *s != c)
			s++;
	}
	arr[w] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = words_counter(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	return (fill_in(s, c, count, arr));
}
