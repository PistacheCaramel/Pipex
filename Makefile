
NAME = pipex
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRCS = main.c ft_pipex.c ft_split.c ft_pipex_utils.c ft_pipex_utils_2.c ft_pipex_utils3.c

OBJS = ${SRCS:.c=.o}

$(NAME): $(OBJS)
	 ${CC} ${FLAGS} ${OBJS} -o ${NAME}

all:	 ${NAME}

clean:	
	 ${RM} ${OBJS}

fclean:	clean 
	 ${RM} ${NAME}

re: fclean all

.PHONY: clean all fclean re

