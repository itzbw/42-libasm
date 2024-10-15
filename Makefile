NAME = libasm.a

SRCS =	ft_strlen.s			\
	ft_strcpy.s			\
	ft_write.s			\
	ft_strcmp.s			\
	ft_read.s			\
	ft_strdup.s

CC = nasm -felf64

OBJS = ${SRCS:.s=.o}

FLAGS	=	-Wall -Wextra -Werror

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

all: ${NAME}

.s.o:
	${CC} -o $@ $?

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf $(NAME)
	rm -rf test_main

re: fclean all

.PHONY: all clean fclean re