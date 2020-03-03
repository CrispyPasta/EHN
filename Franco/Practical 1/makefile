
LINKFLAGS = -lcrypto -lssl

build: 
	-rm server client
	gcc server.c $(LINKFLAGS) -o server
	gcc client.c $(LINKFLAGS) -o client

runs:
	./server

runc:
	./client 

clean:
	-rm server client
