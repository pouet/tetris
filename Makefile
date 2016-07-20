SRC_NAME = $(sort main.c frame.c image.c intro.c menuMain.c font.c game.c sfx.c\
		   tetros.c score.c menuHighScore.c menuOpts.c menuGameOver.c menuHelp.c)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SDL_PATH = ./SDL2.framework/Versions/Current
INC_PATH = ./includes/ SDL2.framework/Headers
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -O3
LDFLAGS = $(addprefix -L,$(LIBFT_PATH) $(MLX_PATH) $(SDL_PATH))
LDLIBS = -F . -framework SDL2
NAME = tetris

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@printf "%-50s" "create executable "$(notdir $@)...
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME)
#-g -fsanitize=address
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2\
		@executable_path/SDL2.framework/SDL2 $(NAME)
	@printf "\e[1;32m[OK]\e[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "%-50s" "compiling "$(notdir $<)...
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\e[1;32m[OK]\e[0m\n"

clean:
	@printf "%-50s" "deleting objects..." 
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_PATH)
	@printf "\e[1;32m[OK]\e[0m\n"

fclean: clean
	@printf "%-50s" "deleting executable..." 
	@$(RM) $(NAME)
	@printf "\e[1;32m[OK]\e[0m\n"

re: fclean all
