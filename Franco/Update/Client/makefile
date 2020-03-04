
LINKFLAGS = -lcrypto -lssl

build: 
	-rm client
	gcc client.c $(LINKFLAGS) -o client

run:
	./client 

clean:
	-rm client
