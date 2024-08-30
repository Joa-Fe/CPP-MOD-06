NAME = base

CC = c++

CFLAGS = -std=c++98 -Wall -Wextra -Werror

OBJ_DIR = obj

SRC_DIR = ./

SRC = main.cpp Base.cpp
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "\33[32m--- Base created with success ---\33[0m"

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\33[32m--- Base Cleaned ---\33[0m"

fclean:
	@rm -rf $(OBJ_DIR)
	@echo "\33[32m--- Base Cleaned ---\33[0m"
	@rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: clean fclean all re bonus