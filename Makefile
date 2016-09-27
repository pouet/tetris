SRC_NAME = $(sort main.c frame.c intro.c menuMain.c font.c game.c sfx.c\
		   tetros.c score.c menuHighScore.c menuOpts.c menuGameOver.c menuHelp.c\
		   menuCredits.c)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O3
NAME = tetris

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	SDL_CONFIG = `sdl2-config --cflags --libs`
	INSTALL_NAME_TOOL =
else # Mac OS
	LDFLAGS += -L ./SDL2.framework/Versions/Current
	INC_PATH += SDL2.framework/Headers
	SDL_CONFIG = -F . -framework SDL2
	INSTALL_NAME_TOOL = install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2\
											@executable_path/SDL2.framework/SDL2 $(NAME)
endif


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@printf "%-50s" "create executable "$(notdir $@)...
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME) $(SDL_CONFIG)
	@$(INSTALL_NAME_TOOL)
	@printf "\033[1;32m[OK]\033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "%-50s" "compiling "$(notdir $<)...
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< $(SDL_CONFIG)
	@printf "\033[1;32m[OK]\033[0m\n"

clean:
	@printf "%-50s" "deleting objects..." 
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_PATH)
	@printf "\033[1;32m[OK]\033[0m\n"

fclean: clean
	@printf "%-50s" "deleting executable..." 
	@$(RM) $(NAME)
	@printf "\033[1;32m[OK]\033[0m\n"

re: fclean all
