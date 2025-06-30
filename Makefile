test: test.c DataStructures/LinkedList.c DataStructures/Queue.c
	cc test.c DataStructures/LinkedList.c DataStructures/Queue.c -o test

server: socket-programming/server.c socket-programming/socketutil.c
	gcc socket-programming/server.c socket-programming/socketutil.c -o server
