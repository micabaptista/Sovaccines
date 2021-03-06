# possivel makefile inacabado
OBJ_dir= obj
OBJETOS = main.o #SOVACCINES.o client.o main.o memory.o process.o proxy.o server.o synchronization.o #memory-private.o
SOVACCINES.o =
client.o =
main.o =
memory.o =
process.o =
proxy.o =
server.o =
synchronization.o =
#memory-private.o
CC = gcc

out: $(OBJETOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJETOS)) -lm -o bin/SOVACCINES

%.o: src/%.c $($@)
	$(CC) -I include -o $(OBJ_dir)/$@ -c $<

clean:
	rm -f obj/*
	rm -f bin/SOVACCINES