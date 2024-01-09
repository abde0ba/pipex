/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:44 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/08 16:18:57 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_two(int fd1, int fd2)
{
	if(close(fd1) == -1)
		err_msg(CLOSE_ERR);
	else if(close(fd2) == -1)
		err_msg(CLOSE_ERR);
}

void	first_command(int *pipefd, char **av, char **env)
{
	char	**words;
	char	*com;
	int		infile;

	dup2_handler(pipefd[1], STDOUT_FILENO);
	if (close(pipefd[0]) == -1)
		err_msg(CLOSE_ERR);
	infile = open(av[1], O_RDONLY, 0777);
	if (infile < 0)
		err_msg(OPEN_ERR);
	dup2_handler(infile, STDIN_FILENO);
	words = ft_split(av[2], ' ');
	com = check_cmd(words[0], env);
	if (!com)
		err_msg(CMD_ERR);
	close_two(infile, pipefd[1]);
	if (execve(com, words, env) == -1)
		err_msg(EXECVE_ERR);
	free(words);
	free(com);
	exit(EXIT_SUCCESS);
}

void	second_command(int *pipefd, char **av, char **env)
{
	int		output;
	char	**words;
	char	*com;

	if (close(pipefd[1]) == -1)
		err_msg(CLOSE_ERR);
	dup2_handler(pipefd[0], STDIN_FILENO);
	if (!ft_strlen(av[4]))
		err_msg(FILE_ERR);
	output = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (output < 0)
		err_msg(OPEN_ERR);
	words = ft_split(av[3], ' ');
	dup2_handler(output, STDOUT_FILENO);
	com = check_cmd(words[0], env);
	if (!com)
		err_msg(CMD_ERR);
	if (execve(com, words, env) == -1)
		err_msg(EXECVE_ERR);
	free(words);
	free(com);
	close_two(output, pipefd[0]);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	pid_t	pid1;
	int		tube;

	(void)ac;
	if (ac != 5)
		err_msg(ARGS_ERR);
	tube = pipe(pipefd);
	if (tube == -1)
		err_msg(PIPE_ERR);
	pid = fork();
	if (pid == -1)
		err_msg(FORK_ERR);
	else if (pid == 0)
		first_command(pipefd, av, env);
	if ((pid1 = fork()) == -1)
		err_msg(FORK_ERR);
	else if (pid1 == 0)
		second_command(pipefd, av, env);
	if (wait(NULL) == -1)
			err_msg(WAIT_ERR);
	close_two(pipefd[0], pipefd[1]);
	exit(EXIT_SUCCESS);
}
