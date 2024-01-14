/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:01:49 by abbaraka          #+#    #+#             */
/*   Updated: 2024/01/14 15:22:47 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define FORK_ERR		1
# define PIPE_ERR		2
# define CMD_ERR		3
# define ARGS_ERR		4
# define OPEN_ERR		5
# define EXECVE_ERR		6
# define CLOSE_ERR		7
# define WAIT_ERR		8
# define DUP2_ERR		9
# define DUP_ERR		10

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>

/* GET_NEXT_LINE */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
int		ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s);

/* LIBFT FUNCTIONS */

size_t	ft_strlen(const char *str);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* PIPEX FUNCTIONS */

void	ft_putchar(int fd, char c);
void	ft_putstr(int fd, char *str);
void	err_msg(int err_num);
void	fn_fill(char *dst, char *src);
char	*access_cmd(char *found, char *command);
char	*check_cmd(char *command, char **env);
void	execute_command(char *cmd, char **env);
void	create_process(char *command, char **env);
int		open_a_file(char *name, char *type);
void	open_files(char **av, int ac, int *infile, int *outfile);
void	dup2_handler(int to_dup, int into);
int		dup_handler(int to_dup);
void	wait_hundler(int *p);
void	close_two(int fd1, int fd2);
void	here_doc_fill(int *infile, char **av);
void	last_command(int ac, char **av, char **env, int *std);

#endif	
