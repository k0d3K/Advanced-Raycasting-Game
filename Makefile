DEBUG ?= 0

MLX := mlx/libmlx.a

MAKE := @$(MAKE) --no-print-directory
NAME := cub3D

all: $(NAME)

$(MLX):
	@echo -n "----- Compiling mlx... "
	$(MAKE) -C mlx >/dev/null 2>/dev/null
	@echo done

$(NAME) :$(MLX)
	$(MAKE) -C manda DEBUG=$(DEBUG)

bonus :$(MLX)
	$(MAKE) -C bonus DEBUG=$(DEBUG)

display_clean_message := 1

clean:
	@rm -rf mlx/obj $(MLX)
	$(MAKE) -C bonus clean >/dev/null
	$(MAKE) -C manda clean >/dev/null
	@if [ $(display_clean_message) -eq 1 ] ;\
	then \
		echo "----- Clean done" ;\
	fi

fclean:
	$(MAKE) display_clean_message=0 clean
	$(MAKE) -C bonus fclean >/dev/null
	$(MAKE) -C manda fclean >/dev/null
	$(MAKE) -C mlx clean >/dev/null
	@rm -f $(NAME)
	@echo "----- Fclean done"

re: fclean all

reb: fclean bonus

.PHONY: all clean fclean $(NAME) re reb bonus
