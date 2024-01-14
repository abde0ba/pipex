/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:21:33 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/08 17:47:14 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_newline(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char	*fill_line(char *full, int was_read, char *buffer, int fd)
{
	while (!ft_strchr(full, '\n') && was_read)
	{
		buffer = (char *)malloc((size_t)(BUFFER_SIZE + 1));
		if (!buffer)
			return (free(full), full = NULL, NULL);
		was_read = read(fd, buffer, BUFFER_SIZE);
		if (was_read == -1)
			return (free(buffer), buffer = NULL, free(full), full = NULL, NULL);
		buffer[was_read] = '\0';
		full = ft_strjoin(full, buffer);
		free(buffer);
	}
	return (full);
}

char	*get_next_line(int fd)
{
	static char	*full = NULL;
	char		*buffer;
	char		*tmp;
	int			was_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	was_read = 1;
	buffer = NULL;
	full = fill_line(full, was_read, buffer, fd);
	if (!full || !*full)
		return (free(full), full = NULL, NULL);
	if (!ft_strchr(full, '\n') && ft_strchr(full, '\0'))
		return (buffer = ft_strdup(full), free(full), full = NULL, buffer);
	buffer = ft_substr(full);
	if (!buffer)
		return (free(full), full = NULL, NULL);
	tmp = ft_strdup(full + check_newline(full) + 1);
	free(full);
	full = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (buffer);
}
