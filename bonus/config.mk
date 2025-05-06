# --- rendering
TARGET_FPS := 300

DPY_W := $(shell (xrandr --current | grep '*' | uniq | awk '{print $$1}' | cut -d 'x' -f1) || echo 1920)
DPY_H := $(shell (xrandr --current | grep '*' | uniq | awk '{print $$1}' | cut -d 'x' -f2) || echo 1080)
ifneq ($(DEBUG), 0)
	TRUE_DPY_W := $(shell echo $$(($(DPY_W) / 2)))
else
	TRUE_DPY_W := $(DPY_W)
endif

N_THREADS := $(shell echo $$(($$(cat /proc/cpuinfo | grep processor | uniq | wc -l || echo 8) - 1)))
N_THREADS := $(shell \
	if [ $(N_THREADS) -lt 1 ] ; \
	then \
		echo 1 ; \
	else \
		echo $(N_THREADS) ; \
	fi)
N_SLICE_THREADS := $(shell \
	if [ $(N_THREADS) -gt 2 ] ; \
	then \
		echo $$(($(N_THREADS) - 2)) ; \
	elif [ $(N_THREADS) -gt 1 ] ; \
	then \
		echo $$(($(N_THREADS) - 1)) ; \
	else \
		echo 1 ; \
	fi)

N_PIXEL_PER_SLICE := $(shell echo $$(($(TRUE_DPY_W) / $(N_SLICE_THREADS) + 1)))

# --- game
G := 9.81f
FOV := 60.0f # deg
DOOR_THICKNESS := 0.1f
PLAYER_SPEED := 3.0f
SPIN_SPEED := 60.0f # deg/s
COL_DIST := 0.3f
MAX_ENTITY_SIZE := 0.99f

# --- minimap
MMAP_VIEW_WIDE := 10 # Nb of tiles in the minimap radius
MMAP_RADIUS := 100 # pixels
MMAP_ROT := 1 # Set to 0 to disable the minimap rotation
BLUR_FACTOR := 2 # number of pixels used for averaging map blur

# --- debug ui
UI_SCALE := 30 # pixels

CONFIG := WIN_W=$(DPY_W) WIN_H=$(DPY_H) TRUE_WIN_W=$(TRUE_DPY_W) TARGET_FPS=$(TARGET_FPS) \
		N_THREADS=$(N_THREADS) N_SLICE_THREADS=$(N_SLICE_THREADS) N_PIXEL_PER_SLICE=$(N_PIXEL_PER_SLICE) \
	G=$(G) FOV=$(FOV) DOOR_THICKNESS=$(DOOR_THICKNESS) PLAYER_SPEED=$(PLAYER_SPEED) SPIN_SPEED=$(SPIN_SPEED) \
		COL_DIST=$(COL_DIST) MAX_ENTITY_SIZE=$(MAX_ENTITY_SIZE) \
	MMAP_VIEW_WIDE=$(MMAP_VIEW_WIDE) MMAP_RADIUS=$(MMAP_RADIUS) MMAP_ROT=$(MMAP_ROT) BLUR_FACTOR=$(BLUR_FACTOR) \
	UI_SCALE=$(UI_SCALE)

CONFIG := $(addprefix -D, $(CONFIG))