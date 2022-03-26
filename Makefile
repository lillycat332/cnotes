CC=clang
CFLAGS=-Wno-nullability-completeness -Wno-nullability-extension -Wall -pedantic

cnotes: src/main.c
	$(CC) -o build/cnotes src/main.c $(CFLAGS)


