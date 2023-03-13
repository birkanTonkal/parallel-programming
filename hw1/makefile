CC=gcc
CFLAGS=-I.
DEPS = hellomake.h
OBJ = 18050111060.o hellofunc.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
