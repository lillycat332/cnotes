CC=clang
CFLAGS=-Wno-nullability-completeness

cnotes: src/main.c
	$(CC) -o build/cnotes src/main.c $(CFLAGS)


