
LINKFLAGS = -lcrypto -lssl

build: 
	-rm client
	gcc client.c $(LINKFLAGS) -o client

run:
	./client Certificates/cert.crt

clean:
	-rm client
