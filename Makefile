NAME=pipex
SRCS= Mandatory/cmds_utils.c Mandatory/errors.c Mandatory/ft_split.c Mandatory/pipex.c Mandatory/str_funs1.c Mandatory/str_funs2.c
OBJS= $(SRCS:.c=.o)
BONUS_SRCS= Bonus/cmds_utils_bonus.c Bonus/errors_bonus.c Bonus/ft_split_bonus.c Bonus/get_next_line.c Bonus/get_next_line_utils.c Bonus/pipex_bonus.c Bonus/str_funs1_bonus.c Bonus/str_funs2_bonus.c
BONUS_OBJS= $(BONUS_SRCS:.c=.o)
HEADER= Mandatory/pipex.h
BONUS_HEADER=Bonus/pipex_bonus.h
CC=cc
CFLAGS= -Wall -Wextra -Werror
RM= rm -rf

$(NAME):$(HEADER) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o : %.c 
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: $(BONUS_HEADER) $(BONUS_OBJS)
		$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME)

clean: 
		$(RM) $(BONUS_OBJS) $(OBJS)

fclean: clean
		$(RM) $(NAME)
re: fclean all