OBJ_DIR := ./obj/
SOURCE_DIR := ./src/
INCLUDE_DIRS := ./include/ ./..
LIBFT := ../libft.a
NAME := $(LIBFT)

INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))

C_FILES :=	int_list char_list str_list generic_list string_builder string_builder_state  list_free

C_FILES := $(addsuffix .c, $(C_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(C_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

all: $(NAME)

$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.c
	@cc $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@ar rcs $@ $(OBJECTS)

clean:
	@rm -rf $(OBJ_DIR)

re: clean all

.PHONY: all clean re
