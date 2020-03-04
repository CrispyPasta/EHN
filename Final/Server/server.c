/**
 * @file server.c
 * @author EHN Group 16 (WA Fourie, MB Hartman, FM van Tonder)
 * @date 4 March 2020
 * @brief SSL web server implementation
 * This implementation creates an SSL server that takes requests from clients and returns local html pages and other files.
 */

#include<stdio.h>
#include<openssl/ssl.h>
#include<openssl/bio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

/**
 * @brief A function that writes the contents of a file to the bio buffer.
 * @param bio A bio object whose buffer will be read to.
 * @param page The location of the file to read from.
 */
void write_page(BIO * bio, const char * page)
{

    FILE * f;
    int bytesread = 0;
    unsigned char buf[512];

    f = fopen(page,"rt");

    if (!f){
        fprintf(stderr,"could not open the page\n");
        return;
    }

    while(1){

        bytesread = fread(buf,sizeof(unsigned char),512,f);

        if (bytesread == 0){
            break;
        }

        if (BIO_write(bio, buf, bytesread)<=0){  // write to BIO connection
            fprintf(stderr,"Write failed \n");
            break;
        }
    }

    fclose(f);

    return;
}

/**
 * @brief Handles requests of connected clients.
 * Determines whether a client is terminal or web browser based. Sends the corresponding request to the client.
 * @param connectBIO The BIO object for the connected client.
 */
void clientHandler(BIO * connectBIO) // Handles GET requests from clients
{
    unsigned char buf[512];
  
    if (BIO_do_handshake(connectBIO) <= 0){
        fprintf(stderr,"handshake failed\n");
        return;
    }

    BIO_read(connectBIO,buf,512);   // Read message from the client

    if(strstr(buf,"GET") == NULL){  // Terminal Client
        write_page(connectBIO,buf); // Write page to client
        BIO_flush(connectBIO);     // Send buffer EOF
	    BIO_free_all(connectBIO);   // Close connect socket
    }
    else{   // Web browser client
        char * sub = buf + 5;   // remove "GET /" from the buffer string
        char pageRequest[512];  // request to handle
        int found = 0;  //  the space at the end of the request has not been found
        for (int i = 0; i < strlen(sub) && found == 0;i++){ // copy sub into pageRequest up to the first space.
            if(sub[i] == ' '){
                found = 1;  //  Space was found -> end loop.
            }
            else{
                pageRequest[i] = sub[i]; // copy sub character into pageRequest
            }
        }

        BIO_puts(connectBIO, "HTTP/1.1 200 OK\r\n\r\n\r\n"); //  Send OK to web browser

        if (strlen(pageRequest) == 0){ // Send default page
            write_page(connectBIO,"Website/Default_Page.html"); //  write default page to buffer
            BIO_flush(connectBIO);  // send buffer EOF
            BIO_free(connectBIO);   //  close connect socket

        }
        else{   // send requested file
            write_page(connectBIO,pageRequest); // write requested file or page to the buffer
            BIO_flush(connectBIO);  // send buffer EOF
            BIO_free_all(connectBIO); // close connect socket
           
        }
    }

    return;
}

/**
 * @brief A function that handles newly connected threads and calls the clientHandler with the connected thread bio.
 * @param connectBIO A newly connected BIO.
 */
void * threadHandler(void * connectBIO) // Handles newly created threads
{

    BIO *threadBIO = (BIO *)connectBIO; // Make a new Thread BIO
    clientHandler(threadBIO); // Call client handler to handle the client's request
    pthread_exit(NULL); // delete the thread

}

/**
 * @brief The main function that does initial server startup.
 * Sets up the server on port 6969. Loads the certificate and private keys. Waits for clients to connect. Makes new threads for connected clients
 * @param argv[1] Stores the location of the web certificate.
 * @param argv[2] Stores the location of the web private key.
 */
int main(int argc,char* argv[])
{

    SSL_load_error_strings(); 
    SSL_library_init(); // initialise ssl library

    SSL_CTX * context;
    SSL * ssl;
    BIO * sslBIO, * acceptBIO, * connectBIO;

    const char * webCert = argv[1]; // Server certificate 
    const char * webKey = argv[2];  //  Server private key
    char * port = "6969";    // server port number
    
    // printf("Enter port number: ");
    // scanf("%s", port);  // get port number from user input

    context = SSL_CTX_new(SSLv23_server_method()); // Create SSL context
    if (context == NULL){   // failed to create SSL context
        fprintf(stderr,"Failed to create the SSL context\n");
        return 0;
    }

    if(SSL_CTX_use_certificate_file(context,webCert, SSL_FILETYPE_PEM) <= 0){ // Load certificate
	    fprintf(stderr,"Certificate error\n"); // Certificate failed
	    return 0;
    }
    
    if (SSL_CTX_use_PrivateKey_file(context,webKey,SSL_FILETYPE_PEM) <= 0) { // Load certificate private key
	    fprintf(stderr,"Private key error\n"); // key failed
        return 0;
    }

    sslBIO = BIO_new_ssl(context,0); // Create SSL BIO object
    if (sslBIO == NULL){
        fprintf(stderr,"Failed retrieving the BIO object \n");
        return 0;
    }

    BIO_get_ssl(sslBIO,&ssl);
    SSL_set_mode(ssl,SSL_MODE_AUTO_RETRY); // Disable retries

    acceptBIO = BIO_new_accept(port);   // create new listening BIO on port
    BIO_set_accept_bios(acceptBIO, sslBIO); //

    if (BIO_do_accept(acceptBIO) <= 0){ // wait for connection
        fprintf(stderr, "Error accepting the socket\n");
        BIO_free(acceptBIO);
        return 0;
    }
  
    BIO_set_nbio_accept(acceptBIO,0); // set to blocking mode 

    for (;;){   // indefinitely accepts connecting bios

        if (BIO_do_accept(acceptBIO) <= 0){ // wait for connection
            fprintf(stderr, "Error connecting the socket\n"); // connection failed
        }
        else{   // connection successful -> create new connection thread
            
            connectBIO = BIO_pop(acceptBIO);    // Retrieve connect BIO from accept BIO
            
            pthread_t tid;  // new thread 
            if (pthread_create(&tid, NULL, threadHandler,connectBIO) != 0){ // create new thread and call thread handler
                fprintf(stderr, "Error creating the thread\n"); // Error creating the thread
            }

            usleep(420); 
        }

    }

    BIO_free(acceptBIO); // Clear the acceptBIO

    return 0;
}

