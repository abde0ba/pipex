/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:44 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/14 13:12:34 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		execute_command(command, env);
	}
	else
	{
		dup2_handler(pipefd[0], STDIN_FILENO);
		close_two(pipefd[0], pipefd[1]);
	}
}

void	here_doc_fill(int *infile, char **av)
{
	char	*str;

	ft_putstr(STDOUT_FILENO, "heredoc > ");
	str = get_next_line(0);
	while (str[ft_strlen(av[2])] != '\n'
		&& ft_strncmp(str, av[2], ft_strlen(str)) != 0)
	{
		write(*infile, str, ft_strlen(str));
		ft_putstr(STDOUT_FILENO, "heredoc > ");
		free(str);
		str = NULL;
		str = get_next_line(0);
		if (str[ft_strlen(av[2])] == '\n'
			&& !ft_strncmp(str, av[2], ft_strlen(av[2])))
			break ;
	}
	free(str);
}

int	here_doc_fn(int	*cmd_number, char **av, int ac, int *outfile)
{
	int		infile;

	if (ac < 6)
		err_msg(ARGS_ERR);
	*cmd_number = 3;
	infile = open("/tmp/.here_tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	here_doc_fill(&infile, av);
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

void	last_command(int ac, char **av, char **env, int *std)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		err_msg(FORK_ERR);
	if (pid == 0)
		execute_command(av[ac - 2], env);
	else
	{
		dup2_handler(std[0], STDIN_FILENO);
		dup2_handler(std[1], STDOUT_FILENO);
		close_two(std[0], std[1]);
		while (wait(NULL) != -1)
			;
	}
}

int	main(int ac, char **av, char **env)
{
	int		cmd_number;
	int		infile;
	int		outfile;
	int		std[2];

	std[0] = dup_handler(STDIN_FILENO);
	std[1] = dup_handler(STDOUT_FILENO);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		infile = here_doc_fn(&cmd_number, av, ac, &outfile);
	else
	{
		cmd_number = 2;
		open_files(av, ac, &infile, &outfile);
	}
	dup2_handler(infile, STDIN_FILENO);
	while (cmd_number < ac - 2)
		create_process(av[cmd_number++], env);
	unlink("/tmp/.here_tmp");
	dup2_handler(outfile, STDOUT_FILENO);
	last_command(ac, av, env, std);
	close_two(infile, outfile);
	return (0);
}
