CC :=clang
CCVERSION = $(shell $(CC) -dumpversion)
CFLAGS :=-Wno-nullability-completeness -Wno-nullability-extension -Wall -pedantic
BUILD_DIR := build
SRCS := src/main.c

all: |$(BUILD_DIR)
	@echo -n 'building with: '
	$(CC) --version | sed 1q
	$(CC) -o $(BUILD_DIR)/cnotes $(SRCS) $(CFLAGS)

$(BUILD_DIR):
	@echo "Folder $(BUILD_DIR) does not exist, creating it..."
	mkdir -p $@

