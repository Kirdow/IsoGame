TARGET_EXEC := isogame

BUILD_DIRS := ./build
SRC_DIRS := ./src ./include
DIST_DIR := ./dist

SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS) -MMD -MP `pkg-flags --cflags sdl2`
LDFLAGS := `pkg-config --libs sdl2`

all: build

run: build
	$(DIST_DIR)/$(TARGET_EXEC)

build: $(DIST_DIR)/$(TARGET_EXEC)

$(DIST_DIR)/$(TARGET_EXEC): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.cflags
	mkdir --o $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm -r $(DIST_DIR)

# Include the .d makefiles.
-include $(DEPS)
