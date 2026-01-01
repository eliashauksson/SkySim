BUILD_DIR := build
TARGET := MyApp
COMPILE_COMMANDS := compile_commands.json

.PHONY: all configure build run clean re

all: build

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	ln -sf $(BUILD_DIR)/$(COMPILE_COMMANDS) $(COMPILE_COMMANDS)

build: configure
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(COMPILE_COMMANDS)

re: clean all
