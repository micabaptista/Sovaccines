# possivel makefile inacabado
OBJ_dir= obj
OBJETOS = sovacinnes.o memory.o synchronization.o client.o proxy.o server.o process.o main.o
sovacinnes.o =
client.o =
main.o =
memory.o =
process.o =
proxy.o =
server.o =
synchronization.o =
memory-private.o =
CC = gcc
FLAGS = -pthread -lrt -I -g

vpath %.o $(OBJ_dir)

out: $(OBJETOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJETOS)) -pthread  -g -lrt -lm -o Sovacinnes

%.o: src/%.c $($@)
	$(CC) $(FLAGS) -o $(OBJ_dir)/$@ -c $<

clean:
	rm -f obj/*
	rm -f bin/SOVACCINES