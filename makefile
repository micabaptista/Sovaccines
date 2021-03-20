# possivel makefile inacabado
OBJ_dir= obj
OBJETOS = memory.o synchronization.o client.o proxy.o server.o process.o main.o
client.o =
main.o =
memory.o =
process.o =
proxy.o =
server.o =
synchronization.o =
memory-private.o =
CC = gcc
FLAGS = -lrt -I

out: $(OBJETOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJETOS)) -lm -o bin/SOVACCINES

%.o: src/%.c $($@)
	$(CC) $(FLAGS) include -o $(OBJ_dir)/$@ -c $<

clean:
	rm -f obj/*
	rm -f bin/SOVACCINES