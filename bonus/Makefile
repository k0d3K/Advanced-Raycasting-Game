CFLAGS := -Wall -Wextra -Werror
ifneq ($(DEBUG), 0)
ifndef display_clean_message
$(info WARNING: building with debug flag)
endif
CFLAGS := $(CFLAGS) -DDEBUG -g
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

C_FILES := main dt map_utils \
	$(addprefix inputs/, inputs mouse) \
	$(addprefix loop/, loop_logic end_screen_loop game_loop title_screen_loop \
		game_flow no_debug debug movements player_management select_gun_img) \
	$(addprefix minimap/, minimap minimap_drawing minimap_utils) \
	$(addprefix physic/, physic collisions collisions_utils) \
	$(addprefix rendering/, rendering rendering_draw_faces rendering_thread rendering_utils skybox render_hurt_effect render_stats render_life_bar) \
	$(addprefix raycast/, raycast_list raycast_calc_dist raycast_utils raycast_next_coord raycasts raycast_doors) \
	$(addprefix geo/, point vec2 vec3 intersection) \
	$(addprefix gfx/, gfx_init gfx_deinit gfx_draw gfx_atlas gfx_text img texture bitmap gfx_line) \
	$(addprefix parsing/, map_parsing map_height_player check_surroundings entities_parsing parsing_utils adventure_parse adventure_parse_2) \
	$(addprefix loading_scene/, set_variables read_file read_textures read_sprites read_utils) \
	$(addprefix entity/, entity entity_list entity_utils) \
	$(addprefix entity/pathfinding/, node_pool node_list node_list_alloc pathfinding \
		pathfinding_impl pathfinding_resources pathfinding_adjacent_nodes pathfinding_debug \
		pathfinding_h_cost pathfinding_can_cross_diagonal_node) \
	$(addprefix utils/, tab_utils geo_utils error time_utils thread_utils scene_utils crc32 dict dict_mem)

C_FILES := $(addsuffix .c, $(C_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(C_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

N_FILES := $(words $(OBJECTS))

include libft/Functions.mk
include config.mk

all: $(NAME)

$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.c
	$(call echo_progress, $<)
	@cc $(CFLAGS) $(CONFIG) $(INCLUDE_DIRS) -c $< -o $@

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
