N := 1
BAR_WIDTH ?= 30

ifndef N_FILES
$(error N_FILES not defined)
endif

define echo_progress
	$(eval perc := $(shell expr 100 '*' $(N) / $(N_FILES)))
	$(eval n_full := $(shell expr $(perc) '*' $(BAR_WIDTH) / 100))
	$(eval n_space := $(shell expr $(BAR_WIDTH) - $(n_full)))
	
	@if [ $(N) -eq 1 ] ; \
	then \
		echo "Compiling $(NAME)..." ; \
	else \
		echo -n "\e[A" ; \
	fi ; \
	echo -n "\e[K  \e[0;31m[" ; \
	for i in `seq $(n_full)` ; \
	do \
		echo -n '=' ; \
	done ; \
	echo -n '>' ; \
	for i in `seq $(n_space)` ; \
	do \
		echo -n ' ' ; \
	done ; \
	echo -n "]    \e[0;32m$(1)\e[m\n" ; \
	if [ $(N) -eq $(N_FILES) ] ; \
	then \
		echo "\e[5;92mDone\e[m\n" ; \
	fi
	
	$(eval N := $(shell expr $(N) + 1))
endef
