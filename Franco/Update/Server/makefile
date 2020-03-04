
LINKFLAGS = -lcrypto -lssl -lpthread

build: 
	-rm server
	gcc server.c $(LINKFLAGS) -o server

server:
	gcc server.c $(LINKFLAGS) -o server

run:
	./server Certificates/webServCert.crt Certificates/webServ.key

clean:
	-rm server
