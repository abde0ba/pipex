/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:47 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/07 14:55:31 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fn_fill(char *dst, char *src)
{
	int	i;
	int	dlen;

	i = 0;
	dlen = ft_strlen(dst);
	while (src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
}

char	*access_cmd(char *found, char *command)
{
	char	**split;
	int		i;
	char	*cmd;

	split = ft_split(found, ':');
	i = 0;
	while (split[i])
	{
		cmd = malloc(ft_strlen(split[i]) + ft_strlen(command) + 2);
		if (!cmd)
			return (NULL);
		cmd[0] = '\0';
		fn_fill(cmd, split[i]);
		fn_fill(cmd, "/");
		fn_fill(cmd, command);
		if (access(cmd, F_OK) == 0)
		{
			free(split);
			return (cmd);
		}
		free(cmd);
		cmd = NULL;
		i++;
	}
	return (NULL);
}

char	*check_cmd(char *command, char **env)
{
	int		i;
	char	*found;
	char	*cmd;

	i = 0;
	found = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
		{
			found = ft_strtrim(env[i], "PATH=");
			break ;
		}
		i++;
	}
	if (found)
	{
		cmd = access_cmd(found, command);
		free(found);
		if (cmd)
			return (cmd);
	}
	return (NULL);
}
