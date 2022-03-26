CC=clang
CFLAGS=-Wno-nullability-completeness

cnotes: main.c
	$(CC) -o cnotes main.c $(CFLAGS)
