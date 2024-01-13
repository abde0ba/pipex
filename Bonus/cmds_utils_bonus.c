/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:47 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/12 22:23:53 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		cmd[0] = '\0';
		fn_fill(cmd, split[i]);
		fn_fill(cmd, "/");
		fn_fill(cmd, command);
		if (access(cmd, F_OK | X_OK) == 0)
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

void	execute_comamnd(char *cmd, char **env)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(cmd, ' ');
	path = check_cmd(cmd_args[0], env);
	if (ft_strchr(cmd, '/'))
	{
		if (execve(cmd, NULL, env) == -1)
			err_msg(EXECVE_ERR);
	}
	else
	{
		if (!path)
			err_msg(CMD_ERR);
		if (execve(path, cmd_args, env) == -1)
			err_msg(EXECVE_ERR);
	}
	free(cmd_args);
}

int	open_a_file(char *name, char *type)
{
	int	filename;

	filename = 0;
	if (ft_strncmp(type, "infile", ft_strlen("infile")) == 0)
	{
		filename = open(name, O_RDONLY, 0777);
		if (filename == -1)
			err_msg(OPEN_ERR);
	}
	else if (ft_strncmp(type, "outfile", ft_strlen("outfile")) == 0)
	{
		filename = open(name, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (filename == -1)
			err_msg(OPEN_ERR);
	}
	else if (ft_strncmp(type, "outfile_heredoc",
			ft_strlen("outfile_heredoc")) == 0)
	{
		filename = open(name, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (filename == -1)
			err_msg(OPEN_ERR);
	}
	return (filename);
}
