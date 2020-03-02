#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>
#include <openssl/rand.h>
#include <stdbool.h>
//this one will attempt to be the server for the practical

bool accept_connection(int portnumber);

int main() {
    printf("REEEEEEEE\n");
    SSL_CTX * context;
    SSL * ssl;
    BIO *acc, *bio;

    ERR_load_BIO_strings();
    SSL_load_error_strings();   //for better error messages
    OpenSSL_add_all_algorithms();   //this adds algorithms, I assume
    SSL_library_init();         //init ssl library so other stuff will work

    context = SSL_CTX_new(SSLv23_method());
    if (context == NULL){
        printf("Failed to set SSL context.\n");
    }

    accept_connection(6968);
    printf("shite\n");
    return 0;
}

/**
 * @brief Accepts an incoming connection on the given port number.
 * @param p The port number
 */
bool accept_connection(int p){
    printf("Waiting for incoming connection.\n");
    BIO * listen_bio;
    listen_bio = BIO_new_accept("6968");

    //Set up the socket
    if (BIO_do_accept(listen_bio) <= 0){
        printf("The connection failed.\n");
        BIO_free(listen_bio);
        return false;
    }

    //set the mode to blocking mode
    BIO_set_nbio_accept(listen_bio, 0);
    if (BIO_do_accept(listen_bio) <= 0){
        printf("Error accepting the socket.\n");
        BIO_free(listen_bio);
        return false;
    }

    return true;    //return true if the connection was successful
}
