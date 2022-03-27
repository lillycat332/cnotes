CC :=clang
CFLAGS :=-Wno-nullability-completeness -Wno-nullability-extension -Wall -pedantic
BUILD_DIR := build
SRCS := src/main.c

all: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/cnotes $(SRCS) $(CFLAGS)

$(BUILD_DIR):
	@echo "Folder $(BUILD_DIR) does not exist, creating it..."
	mkdir -p $@

