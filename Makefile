NAME = container

SRCS	= main.cpp
HEADERS	= 

CC			= clang++ 

CPP_FLAGS	= -Wall -Werror -Wextra -std=c++98
# CPP_FLAGS	= -Wall -Werror -Wextra 

OBJS		= $(SRCS:%.cpp=%.o)

RM			= rm -rf

all: $(NAME)

$(NAME): $(SRCS) ${HEADERS}
	$(CC) $(CPP_FLAGS) $(SRCS) -o std$(NAME)
	$(CC) $(CPP_FLAGS) -D NAMESPACE=ft $(SRCS) -o ft$(NAME)


%.o: %.cpp $(HEADERS)
	$(CC) -c $(CPP_FLAGS) $< -o $@

clean:
	$(RM) $(OBJS) ft std 

fclean: clean
	$(RM) *$(NAME)

re: fclean all

test: all
	@clear && echo ------------  std ------------ && ./stdcontainer
.PHONY: all clean fclean re

ft:  all
	@clear && echo ------------  ft ------------ && ./ft${NAME} 
	