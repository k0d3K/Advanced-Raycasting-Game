OBJ_DIR := ./obj/
SOURCE_DIR := ./src/
INCLUDE_DIRS := ./include/ ./..
LIBFT := ../libft.a
NAME := $(LIBFT)

INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))

C_FILES :=	ft_printf ft_vdprintf parse_format parse_format_data util util_number print_decimal print_hexs print_integers

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
