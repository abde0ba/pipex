NAME=pipex
NAME_BONUS=pipex_bonus
SRCS= Mandatory/cmds_utils.c Mandatory/errors.c Mandatory/ft_split.c Mandatory/pipex.c Mandatory/str_funs1.c Mandatory/str_funs2.c
OBJS= $(SRCS:.c=.o)
BONUS_SRCS= Bonus/cmds_utils_bonus.c Bonus/errors_bonus.c Bonus/ft_split_bonus.c Bonus/get_next_line_bonus.c Bonus/get_next_line_utils_bonus.c Bonus/pipex_bonus.c Bonus/str_funs1_bonus.c Bonus/str_funs2_bonus.c
BONUS_OBJS= $(BONUS_SRCS:.c=.o)
HEADER= Mandatory/pipex.h
BONUS_HEADER=Bonus/pipex_bonus.h
CC=cc
CFLAGS= -Wall -Wextra -Werror
RM= rm -rf


$(NAME): $(OBJS) $(HEADER)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJS): %.o : %.c $(BONUS_HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: $(BONUS_OBJS)
		$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME_BONUS)

clean: 
		$(RM) $(BONUS_OBJS) $(OBJS)

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)
		
re: fclean all 