NAME	:=	pipex

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
HEADERS	=	-Iinclude -Ilibft
LIBS	=	-Llibft -lft

VPATH	:=	src
SRC		=	main.c env_utils.c input_handling.c

OBJ_DIR	:=	obj
OBJ		:=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))


all: $(NAME)

$(NAME): $(OBJ) | libft
	@$(CC) $(CFLAGS) $(HEADERS) $^ -o $@ $(LIBS)
	@echo "[$(NAME)] Created binary."

$(OBJ_DIR)/%.o: %.c
	@if [ ! -d "$(OBJ_DIR)" ]; then \
		mkdir $(OBJ_DIR); \
	fi
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "[$(NAME)] Compiled $<."

libft:
	@make -C libft

clean:
	@make -C libft clean
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "[$(NAME)] Removed object files."; \
	fi

fclean: clean
	@make -C libft fclean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "[$(NAME)] Removed binary."; \
	fi

re:	fclean all

.PHONY: all libft clean fclean re
