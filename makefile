#SO-036
#Michael Baptista, 54478
# Afonso Rosa, 54395
# Duarte Pinheiro, 54475
OBJ_dir= obj
OBJETOS = memory.o synchronization.o client.o proxy.o server.o process.o main.o sovacinnes.o
SOVACCINES.o =
client.o =
main.o =
memory.o =
process.o =
proxy.o =
server.o =
synchronization.o =
memory-private.o =
CC = gcc
FLAGS = -pthread -lrt -Wall -lm -g

vpath %.o $(OBJ_dir)

out: $(OBJETOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJETOS)) $(FLAGS) -o bin/SOVACCINES

%.o: src/%.c $($@)
	$(CC) $(FLAGS) -o $(OBJ_dir)/$@ -c $<

clean:
	rm -f obj/*
	rm -f bin/SOVACCINES