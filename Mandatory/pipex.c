/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:44 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/13 11:56:53 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_two(int fd1, int fd2)
{
	if (close(fd1) == -1)
		err_msg(CLOSE_ERR);
	else if (close(fd2) == -1)
		err_msg(CLOSE_ERR);
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

void	first_command(int *pipefd, char **av, char **env)
{
	int		infile;

	dup2_handler(pipefd[1], STDOUT_FILENO);
	if (close(pipefd[0]) == -1)
		err_msg(CLOSE_ERR);
	infile = open(av[1], O_RDONLY, 0777);
	if (infile < 0)
		err_msg(OPEN_ERR);
	dup2_handler(infile, STDIN_FILENO);
	if (close(infile) == -1)
		err_msg(CLOSE_ERR);
	execute_comamnd(av[2], env);
}

void	second_command(int *pipefd, char **av, char **env)
{
	int	output;

	if (close(pipefd[1]) == -1)
		err_msg(CLOSE_ERR);
	dup2_handler(pipefd[0], STDIN_FILENO);
	if (!ft_strlen(av[4]))
		err_msg(FILE_ERR);
	output = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (output < 0)
		err_msg(OPEN_ERR);
	dup2_handler(output, STDOUT_FILENO);
	if (close(output) == -1)
		err_msg(CLOSE_ERR);
	execute_comamnd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	pid_t	pid1;
	int		pipefd[2];
	int		tube;

	(void)ac;
	if (ac != 5)
		err_msg(ARGS_ERR);
	tube = pipe(pipefd);
	if (tube == -1)
		err_msg(PIPE_ERR);
	pid = fork();
	if (pid == 0)
		first_command(pipefd, av, env);
	pid1 = fork();
	if (pid1 == 0)
		second_command(pipefd, av, env);
	close_two(pipefd[0], pipefd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
	return (0);
}
