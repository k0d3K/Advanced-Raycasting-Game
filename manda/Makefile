CFLAGS := -Wall -Wextra -Werror
ifneq ($(DEBUG), 0)
ifndef display_clean_message
$(info WARNING: building with debug flag)
endif
CFLAGS := $(CFLAGS) -g
else
CFLAGS := $(CFLAGS) -O3
endif

NAME := ../cub3D
SOURCE_DIR := ./src/
OBJ_DIR := ./obj/
INCLUDE_DIRS := ./include/ ./libft ../mlx /usr/include/X11

MAKE := @make --no-print-directory
MAKE_LIBFT := $(MAKE) DEBUG=$(DEBUG) -C libft
LIBFT := libft/libft.a
MLX := ../mlx/libmlx.a

INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))

C_FILES := main dt input loop_logic raycast rendering rendering_utils map_utils \
	$(addprefix geo/, point vec2 vec3) \
	$(addprefix gfx/, gfx_init gfx_draw img texture bitmap gfx_line) \
	$(addprefix loading_scene/, read_file read_textures get_colors parsing_and_validation) \
	$(addprefix utils/, tab_utils file_utils geo_utils error)

C_FILES := $(addsuffix .c, $(C_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(C_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

N_FILES := $(words $(OBJECTS))

include libft/Functions.mk

all: $(NAME)

$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.c
	$(call echo_progress, $<)
	@cc $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
#	recursively recreates the source dir folder hierarchy. pretty cool ngl
	@(cd $(SOURCE_DIR) && find . -type d -exec mkdir -p -- $(shell pwd)/$(OBJ_DIR){} \;)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(MLX) -lXext -lX11 -lXrender -lXfixes -lm -lz

$(LIBFT):
	$(MAKE_LIBFT)

display_clean_message := 1

clean:
	$(MAKE_LIBFT) clean
	@rm -rf $(OBJ_DIR)
	@if [ $(display_clean_message) -eq 1 ] ;\
	then \
		echo "----- Clean done" ;\
	fi

fclean:
	$(MAKE_LIBFT) fclean
	$(MAKE) display_clean_message=0 clean
	@echo "----- Fclean done"

.PHONY: all clean fclean
