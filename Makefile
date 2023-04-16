CC = gcc
CLAVES_PATH = claves
SOCKETS_PATH = sockets
CFLAGS = -lrt
OBJS = servidor cliente cliente2
BIN_FILES = servidor cliente cliente2

all: $(OBJS)

libclaves.so: $(CLAVES_PATH)/claves.c
	$(CC) -fPIC -c -o $(CLAVES_PATH)/claves.o $<
	$(CC) -shared -fPIC -o $@ $(SOCKETS_PATH)/sockets.c $(CLAVES_PATH)/claves.o

servidor:  servidor.c operaciones/operaciones.c sockets/sockets.c
	$(CC)  $(CFLAGS) $^ -o $@.out

cliente: cliente.c libclaves.so
	$(CC) -L. -lclaves $(CFLAGS) -o $@.out $< ./libclaves.so -lrt

cliente2: cliente2.c libclaves.so
	$(CC) -L. -lclaves $(CFLAGS) -o $@.out $< ./libclaves.so -lrt
clean:
	rm -f $(BIN_FILES) *.out *.o *.so $(CLAVES_PATH)/*.o data.txt

re:	clean all

.PHONY: all libclaves.so servidor cliente clean re