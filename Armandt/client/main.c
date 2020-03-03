#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#include <openssl/rand.h>
#include <stdbool.h>
#include "string.h"

int main() {
    ERR_load_BIO_strings();
    SSL_load_error_strings();   //for better error messages
    OpenSSL_add_all_algorithms();   //this adds algorithms, I assume
    SSL_library_init();         //init ssl library so other stuff will work

    printf("This is the client program!\n");

    SSL_CTX * context = NULL;
    context = SSL_CTX_new(SSLv23_client_method());

    if (context == NULL){
        printf("Failed to set SSL context.\n");
        return 0;
    }

    BIO * bio;
    bio = BIO_new_ssl(context, 0);


    return 0;
}

