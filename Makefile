

# Color codes
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Name of the program
NAME = run_checker

# Compilation flags
CC		= g++
CFLAGS	= -Wall -Werror -Wextra -std=c++98 

# Source files
SRC = ./checker/checker.cpp

# Compilation rules
all: $(NAME)

$(NAME): $(SRC)
	@echo "$(YELLOW)----- Compiling. Please Wait! -----$(RESET)"
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)----- Compilation completed!  -----$(RESET)"

clean:
	@rm -f $(NAME)

fclean:
	@rm -f $(NAME)
	@rm -f *.obj

re: fclean all

.PHONY: all clean fclean re
