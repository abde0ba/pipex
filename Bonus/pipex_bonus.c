/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:44 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/09 12:20:02 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (!path)
		err_msg(CMD_ERR);
	if (execve(path, cmd_args, env) == -1)
		err_msg(EXECVE_ERR);
	free(cmd_args);
}

void	create_process(char *command, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		err_msg(PIPE_ERR);
	pid = fork();
	if (pid == -1)
		err_msg(FORK_ERR);
	else if (pid == 0)
	{
		dup2_handler(pipefd[1], STDOUT_FILENO);
		close_two(pipefd[0], pipefd[1]);
		execute_comamnd(command, env);
	}
	else
	{
		dup2_handler(pipefd[0], STDIN_FILENO);
		close_two(pipefd[1], pipefd[0]);
	}
}

int	here_doc_fn(int	*cmd_number, char **av, int ac, int *outfile)
{
	int		infile;
	char	*str;

	if (ac < 6)
		err_msg(ARGS_ERR);
	*cmd_number = 3;
	ft_putstr(STDOUT_FILENO, "heredoc > ");
	str = get_next_line(0);
	infile = open("/tmp/.here_tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_strncmp(str, av[2], ft_strlen(str)) != 0 && str[ft_strlen(av[2])] != '\n')
	{
		write(infile, str, ft_strlen(str));
		ft_putstr(STDOUT_FILENO, "heredoc > ");
		str = get_next_line(0);
	}
	if (close(infile) == -1)
		err_msg(CLOSE_ERR);
	infile = open("/tmp/.here_tmp", O_RDONLY, 0777);
	if (infile < 0)
		err_msg(OPEN_ERR);
	*outfile = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (*outfile < 0)
			err_msg(OPEN_ERR);
	return (infile);
}

int	main(int ac, char **av, char **env)
{
	int		cmd_number;
	int		infile;
	int		outfile;
	int		pid;

	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		infile = here_doc_fn(&cmd_number, av, ac, &outfile);
	else
	{
		cmd_number = 2;
		open_files(av, ac, &infile, &outfile);
	}
	dup2_handler(infile, STDIN_FILENO);
	while (cmd_number < ac - 2)
	{
		create_process(av[cmd_number], env);
		cmd_number++;
	}
	unlink("/tmp/.here_tmp");
	dup2_handler(outfile, STDOUT_FILENO);
	wait_hundler(NULL);
	if ((pid = fork()) < 0)
		err_msg(FORK_ERR);
	if (pid == 0)
		execute_comamnd(av[ac - 2], env);
	return (0);
}
