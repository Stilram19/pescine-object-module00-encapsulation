NAME=	graph
SRCS=	Vector2.cpp Graph.cpp main.cpp
FILENAME= input
PNGFILE= Graph.png

OBJS=	${SRCS:.cpp=.o}
CPP=	c++
CPPFLAGS= -Wall -Wextra -Werror -std=c++98
RM= rm -f

%.o: %.cpp
	${CPP} ${CPPFLAGS} -c $^ -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CPP} ${CPPFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS} ${PNGFILE}

fclean: clean
	${RM} ${NAME}

re: fclean all

run: re
	./$(NAME) $(FILENAME)

leaks: re
	valgrind --leak-check=full ./$(NAME) $(FILENAME)