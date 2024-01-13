/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:49 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/12 10:55:39 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FORK_ERR		1
# define PIPE_ERR		2
# define CMD_ERR		3
# define ARGS_ERR		4
# define FILE_ERR		5
# define OPEN_ERR		6
# define EXECVE_ERR		7
# define CLOSE_ERR		8
# define WAIT_ERR		9
# define DUP2_ERR		10

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

/* LIBFT FUNCTIONS */

size_t	ft_strlen(const char *str);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);

/* PIPEX FUNCTIONS */

void	ft_putchar(int fd, char c);
void	ft_putstr(int fd, char *str);
void	err_msg(int err_num);
void	fn_fill(char *dst, char *src);
char	*access_cmd(char *found, char *command);
char	*check_cmd(char *command, char **env);
void	first_command(int *pipefd, char **av, char **env);
void	second_command(int *pipefd, char **av, char **env);
void	dup2_handler(int to_dup, int into);
void	execute_comamnd(char *cmd, char **env);

#endif
