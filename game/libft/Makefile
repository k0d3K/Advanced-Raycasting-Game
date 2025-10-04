CFLAGS := -Wall -Wextra -Werror
ifeq ($(DEBUG), 1)
CFLAGS := $(CFLAGS) -g
else
CFLAGS := $(CFLAGS) -O3
endif

MAKE := @make --no-print-directory
MAKE_SUB = $(MAKE) CFLAGS='$(CFLAGS)' -C

OBJ_DIR := ./obj/
SOURCE_DIR := ./
INCLUDE_DIR := ./
NAME := libft.a

C_FILES :=	atoi \
		strncmp strlen strnstr strdup \
		strchr strrchr \
		strlcat strlcpy \
		isalpha isdigit isalnum isascii isprint  \
		toupper tolower \
		memset bzero memcpy memchr memcmp memmove calloc realloc free_2d \
		substr strjoin strtrim split strendswith \
		itoa \
		strmapi striteri \
		putchar_fd putstr_fd putendl_fd putnbr_fd \
		lstnew lstadd_front lstsize lstlast lstdelone lstadd_back lstclear \
		lstiter lstmap \

C_FILES := $(addprefix ft_, $(C_FILES))
C_FILES := $(C_FILES) get_next_line
C_FILES := $(addsuffix .c, $(C_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(C_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

N_FILES := $(words $(OBJECTS))

include Functions.mk

all: $(NAME)

$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.c
	$(call echo_progress, $<)
	@cc $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

pre_build:
	$(MAKE_SUB) ft_printf
	$(MAKE_SUB) structs

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): pre_build $(OBJ_DIR) $(OBJECTS)
	@ar rcs $@ $(OBJECTS)

display_clean_message := 1

clean:
	@if [ $(display_clean_message) -eq 1 ] ;\
	then \
		echo -n "----- Cleaning libft... " ;\
	fi
	@rm -rf $(OBJ_DIR)
	$(MAKE_SUB) ft_printf clean
	$(MAKE_SUB) structs clean
	@if [ $(display_clean_message) -eq 1 ] ;\
	then \
		echo done ;\
	fi

fclean:
	@echo -n "----- F-Cleaning libft... "
	$(MAKE) display_clean_message=0 clean
	@rm -f $(NAME)
	@echo done

re: fclean all

.PHONY: all clean fclean re pre_build
