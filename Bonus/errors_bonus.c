/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:51 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/14 15:23:54 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(fd, str[i]);
		i++;
	}
}

void	err_msg(int err_num)
{
	if (err_num == PIPE_ERR)
		perror("pipe");
	else if (err_num == FORK_ERR)
		perror("fork");
	else if (err_num == CMD_ERR)
		perror("command");
	else if (err_num == ARGS_ERR)
		ft_putstr(STDERR_FILENO,
			"\033[1;33mPlease provide only required arguments\033[0m");
	else if (err_num == OPEN_ERR)
		perror("open");
	else if (err_num == EXECVE_ERR)
		perror("execve");
	else if (err_num == CLOSE_ERR)
		perror("close");
	else if (err_num == WAIT_ERR)
		perror("wait");
	else if (err_num == DUP2_ERR)
		perror("dup2");
	exit(EXIT_FAILURE);
}

void	dup2_handler(int to_dup, int into)
{
	if (dup2(to_dup, into) < 0)
		err_msg(DUP2_ERR);
}

void	wait_hundler(int *p)
{
	if (wait(p) < 0)
		err_msg(WAIT_ERR);
}
