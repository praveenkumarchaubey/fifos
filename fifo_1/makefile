#VARIABLE DECLARATION
CC = gcc
FLAGS = -c -Wall

#DESTINATION
SRC = src/
HDRS = include/

all : server client

server : server.o
	$(CC) -o server server.o -g

client : client.o
	$(CC) -o client client.o -g

server.o : $(SRC)server.c $(HDRS)header.h
	$(CC) $(FLAGS) $(SRC)server.c -I $(HDRS)

client.o : $(SRC)client.c $(HDRS)header.h
	$(CC) $(FLAGS) $(SRC)client.c -I $(HDRS)

clean :
	rm *.o
	rm server
	rm client

