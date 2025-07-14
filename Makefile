
NAME			=	cub3D
# BONUS_NAME		=	_bonus

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -Ofast -MMD #-g -fsanitize=address -fno-omit-frame-pointer
MLXFLAGS		=	#-DDEBUG=1 -DGLFW_FETCH=OFF

LIBFT_DIR		=	./libs/libft
LIBMLX			=	./libs/MLX42

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	# macOS-specific flags
	CFLAGS  += -DMACOS
	LIBS    = $(LIBMLX)/build/libmlx42.a -lglfw \
	          -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	          -pthread -lm  $(LIBFT_DIR)/libft.a
else ifeq ($(UNAME_S), Linux)
	# Linux-specific flags
	CFLAGS  += -DLINUX
	LIBS    = $(LIBMLX)/build/libmlx42.a -lglfw -ldl -lGL -lm -pthread $(LIBFT_DIR)/libft.a 
endif

#LIBS			=	$(LIBMLX)/build/libmlx42.a -lglfw -pthread -lm $(LIBFT_DIR)/libft.a

HEADERS			=	-I ./include -I $(LIBMLX)/include

SRC				=	$(shell find ./src -iname "*.c")
SRC_DIR			=	./src
OBJ_DIR			=	src_o
# SRC_BONUS_DIR	=	src_bonus
# OBJ_BONUS_DIR	=	src_bonus_o

OBJ				=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


# COLORS
BLUE			= 	\033[38;5;27m
CYAN			= 	\033[38;5;51m
PINK			=	 \033[38;5;211m
GREEN			= 	\033[38;5;72m
TURQ			= 	\033[38;5;37m
WHITE			= 	\033[38;5;15m
YELLOW			= 	\033[38;5;220m
C				=	\033[38;5;
O				=	37
L				=	m
SHIFT			=	$(eval O=$(shell echo $$((($(O)%13)+1))))

LBOR			=	"▌│█║▌║▌║ "
RBOR			= 	" ║▌║▌║█│▌"

all: submodule libft libmlx $(NAME)
	@echo "$(CYAN)"
	@echo "\t⠀⠀⠀⠀⠀⣀⣤⡴⢀⣠⣤⣴⣶⡶⠿⠿⠿⠿⣿⣿⣶⣶⣦⣟⡶⢦⣄⡀⠀⠀⠀"
	@echo "\t⠀⠀⢀⣴⡿⠛⣡⡾⠛⢋⣩⡄⠀⠀⠀⠀⠀⠀⠀⠀⠶⣭⣙⠻⢿⣷⣌⢙⢷⣄⠀"
	@echo "\t⠀⣰⣿⠏⠌⣾⠋⢀⣴⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢳⡄⠙⣿⡆⠀⢻⡆"
	@echo "\t⠀⢿⣿⡄⠀⢿⡄⠘⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⡣⣠⡿⠃⠀⣼⡇"
	@echo "\t⠀⠘⢿⣿⣦⣄⠙⠷⣬⣛⠷⣦⣤⣤⣀⣀⣀⣀⣤⣤⡴⠞⣫⣵⠾⠋⣁⣤⣾⠏⠀"
	@echo "\t⠀⠀⠀⠙⠿⣿⣿⣷⣶⣭⣍⣐⣀⣉⠉⠉⠉⠉⢁⣀⣀⣀⣤⣴⣶⡿⣿⡏⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⢸⣿⡟⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⠿⠿⠿⠛⠛⠩⣁⣴⡿⠃⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠈⢿⣿⣮⣟⠿⣿⣿⣷⣶⣶⣶⣶⣶⣶⣶⣶⣾⠿⠟⠋⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⢀⣾⠟⢿⣿⣿⣶⣭⣉⡉⠉⠉⠉⠩⢍⣩⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠈⢿⣧⣄⠈⠉⠛⠻⠿⠿⠿⣿⣿⢿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⣴⡿⠿⣿⣶⣤⣄⣀⣀⣀⣀⣀⣼⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⠙⢿⣶⣦⣍⣉⡛⠛⠛⠛⠛⣻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⠀⠸⣿⣽⣛⡛⠿⠿⠿⠿⣿⡋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⠿⠿⠿⣯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣟⣛⣛⣻⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "Made By Turmoil!\t  ⠙⡇"
	@echo "$(WHITE)"


libmlx:
	@cmake $(MLXFLAGS) $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@echo "$(YELLOW)Compiling: $(notdir $<)$(WHITE)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME) #-fsanitize=address -fno-omit-frame-pointer

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

SUBMODULES_INITIALIZED := $(shell test -d $(LIBFT_DIR)/.git && test -d $(LIBMLX)/.git && echo yes)

submodule:
ifeq ($(SUBMODULES_INITIALIZED),)
	@echo "\n\n$(CYAN)$(LBOR) Initializing submodules... $(RBOR)$(WHITE)\n\n"
	@git submodule update --init --recursive
endif

clean:
	@echo "\n\t   $(PINK)$(LBOR)Cleaning$(RBOR)$(WHITE)\n"
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "\n\t   $(CYAN)$(LBOR)Clean af$(RBOR)$(WHITE)\n"
	@rm -rf $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re:
	@echo "\n\t$(BLUE)$(LBOR)Awwwww shiiiiiit$(RBOR)$(WHITE)\n"
	@echo "\n\t$(BLUE)$(LBOR)Here we go again$(RBOR)$(WHITE)\n"
	@$(MAKE) fclean
	@$(MAKE) all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re libmlx libft
