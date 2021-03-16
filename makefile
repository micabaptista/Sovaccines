# possivel makefile inacabado
OBJ_dir= obj
OBJETOS =  memory.o #main.o SOVACCINES.o client.o main.o memory.o process.o proxy.o server.o synchronization.o #memory-private.o
SOVACCINES.o =
client.o =
main.o =z
memory.o =
process.o =
proxy.o =
server.o =
synchronization.o =
#memory-private.o
CC = gcc
FLAGS = -lrt -I

out: $(OBJETOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJETOS)) -lm -o bin/SOVACCINES

%.o: src/%.c $($@)
	$(CC) $(FLAGS) include -o $(OBJ_dir)/$@ -c $<

clean:
	rm -f obj/*
	rm -f bin/SOVACCINES