/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:51 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/14 14:42:44 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		ft_putstr(STDERR_FILENO, "Error in creating a pipe.");
	else if (err_num == FORK_ERR)
		ft_putstr(STDERR_FILENO, "Error in making a fork.");
	else if (err_num == CMD_ERR)
		ft_putstr(STDERR_FILENO, "The command could not be found.");
	else if (err_num == ARGS_ERR)
		ft_putstr(STDERR_FILENO,
			"\033[1;33mPlease provide only required arguments\033[0m");
	else if (err_num == FILE_ERR)
		ft_putstr(STDERR_FILENO, "Please provide a valid name for the file.");
	else if (err_num == OPEN_ERR)
		ft_putstr(STDERR_FILENO, "Error in opening the file.");
	else if (err_num == EXECVE_ERR)
		ft_putstr(STDERR_FILENO, "Error in execve function");
	else if (err_num == CLOSE_ERR)
		ft_putstr(STDERR_FILENO, "Error in closing the file.");
	else if (err_num == WAIT_ERR)
		ft_putstr(STDERR_FILENO, "Error in waiting for another process.");
	else if (err_num == DUP2_ERR)
		ft_putstr(STDERR_FILENO, "Error in redirecting the file descriptor");
	exit(EXIT_FAILURE);
}

void	dup2_handler(int to_dup, int into)
{
	if (dup2(to_dup, into) < 0)
		err_msg(DUP2_ERR);
}
