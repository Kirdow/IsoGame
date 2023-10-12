TARGET_EXEC := isogame

BUILD_DIR := ./build
SRC_DIRS := ./src ./include
DIST_DIR := ./dist

SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

SDL_INCLUDE_PATH := $(shell brew --prefix sdl2)/include/SDL2
CFLAGS := $(INC_FLAGS) -I$(SDL_INCLUDE_PATH) -MMD -MP

SDL_LIBRARY_PATH := $(shell brew --prefix sdl2)/Llibs
LDFLAGS := L$(SDL_LIBRARY_PATH) -lSDL2

all: build

run: build
	$(DIST_DIR)/$(TARGET_EXEC)

build: $(DIST_DIR)/$(TARGET_EXEC)

$(DIST_DIR)/$(TARGET_EXEC): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
.clean:
	rm -r $(BUILD_DIR)
	rm -r $(DIST_DIR)

# include the .d makefiles.
-include $(DEPS)
