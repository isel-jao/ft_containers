NAME = container

SRCS	= main.cpp
HEADERS	= vector.hpp

CC			= clang++ -Wall -Werror -Wextra 

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
	@clear && echo ------------  std ------------ && ./stdcontainer
.PHONY: all clean fclean re

ft:  all
	@clear && echo ------------  ft ------------ && ./ft${NAME} 
	