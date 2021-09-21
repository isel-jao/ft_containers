NAME = container

SRCS	= main.cpp
HEADERS	= vector.hpp

CC			= clang++ -Wall -Werror -Wextra -std=c++98

CPP_FLAGS	= -Wall -Werror -Wextra -std=c++98
LD			= $(CC)

OBJS		= $(SRCS:%.cpp=%.o)

RM			= rm -rf

all: $(NAME)

$(NAME): $(SRCS) ${HEADERS}
	$(CC) $(SRCS) -o std$(NAME)
	$(CC) -D NAMESPACE=ft $(SRCS) -o ft$(NAME)


%.o: %.cpp $(HEADERS)
	$(CC) -c $(CPP_FLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) *$(NAME)

re: fclean all

test: all
	@clear && ./std${NAME} 
.PHONY: all clean fclean re

ft:  all
	@clear && ./ft${NAME} 
	