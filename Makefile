DEBUG ?= 0

MLX := mlx/libmlx.a

MAKE := @$(MAKE) --no-print-directory
NAME := raycast_game

all: $(NAME)

$(MLX):
	@echo -n "----- Compiling mlx... "
	@$(MAKE) -C mlx >/dev/null 2>/dev/null
	@echo done

$(NAME) :$(MLX)
	@cd textures\
	&& ./font_convert.py BabyPlums-rv2gL.ttf 40 2>/dev/null\
	&& ./bmp_convert.py *.jpg *.png
	@$(MAKE) -C game DEBUG=$(DEBUG)

display_clean_message := 1

clean:
	@rm -rf mlx/obj $(MLX)
	@$(MAKE) -C game clean >/dev/null
	@if [ $(display_clean_message) -eq 1 ] ;\
	then \
		echo "----- Clean done" ;\
	fi

fclean:
	$(MAKE) display_clean_message=0 clean
	$(MAKE) -C game fclean >/dev/null
	$(MAKE) -C mlx clean >/dev/null
	@rm -f $(NAME)
	@rm -f textures/*.bmp
	@echo "----- Fclean done"

re: fclean all

.PHONY: all clean fclean re
