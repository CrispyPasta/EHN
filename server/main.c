#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#include <openssl/rand.h>
#include <stdbool.h>
#include "string.h"
//this one will attempt to be the server for the practical

static bool accept_connection(int portnumber);

int main() {
    printf("REEEEEE EE\n");
    SSL_CTX * context;

    ERR_load_BIO_strings();
    SSL_load_error_strings();   //for better error messages
    OpenSSL_add_all_algorithms();   //this adds algorithms, I assume
    SSL_library_init();         //init ssl library so other stuff will work

    context = SSL_CTX_new(SSLv23_server_method());
    if (context == NULL){
        printf("Failed to set SSL context.\n");
    }

    int added = SSL_CTX_use_certificate_file(context, "/home/armandt/Documents/EHN/EHN/server/webServ.crt", SSL_FILETYPE_PEM);

    if (added != 1) {
        printf("Failed to add certificate to context.\n");
        return 0;
    }

    added = SSL_CTX_use_PrivateKey_file(context, "/home/armandt/Documents/EHN/EHN/server/webServ.key", SSL_FILETYPE_PEM);

//    if (added != 1){
//        printf("Failed to add key to context.\n");
//        return 0;
//    }

    //make connection using BIO
    int p = 6969;

    if (p < 2000){  //use >=2000 to avoid using reserved port numbers.
        printf("Please enter a port number greater than 1999.\n");
        return 0;
    }

    printf("Waiting for connection on port %u.\n", p);
    BIO * listen_bio;
    char port_string[4];        //arbitrarily choose a port number length of 4.
    sprintf(port_string, "%u", p);
    listen_bio = BIO_new_accept(port_string);

    //Set up the socket
    if (BIO_do_accept(listen_bio) <= 0){
        printf("Error setting up the listening socket.\n");
        BIO_free(listen_bio);
    }

    //set the mode to blocking mode
    BIO_set_nbio_accept(listen_bio, 0); //blocking mode makes it wait until a connection is made
    if (BIO_do_accept(listen_bio) <= 0){
        printf("Error accepting the socket.\n");
        BIO_free(listen_bio);
    }


    printf("Done\n");
    return 0;
}

/**
 * @brief Accepts an incoming connection on the given port number.
 * @param p The port number
 */
static bool accept_connection(int p){
    int numCalls = 0;

}
