NAME	:=	pipex

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
HEADERS	=
LIBS	=

VPATH	:=	src
SRC		=	main.c

OBJ_DIR	:=	obj
OBJ		:=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(HEADERS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: %.c
	@if [ ! -d "$(OBJ_DIR)" ]; then \
		mkdir $(OBJ_DIR); \
	fi
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "Removed object files."; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "Removed binary."; \
	fi

re:	fclean all

.PHONY: all clean fclean re
