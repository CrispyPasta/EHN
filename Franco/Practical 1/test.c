#include<stdio.h>
#include<openssl/ssl.h>
#include<openssl/bio.h>

int main()
{


    SSL_library_init();

    BIO *abio, *cbio;

    abio = BIO_new_accept("69420"); // new listening BIO


    if (BIO_do_accept(abio) <= 0){  // set up socket
        fprintf(stderr, "error setting up the listening socket\n");
        BIO_free(abio);
        return 0;
    }

    BIO_set_nbio_accept(abio,0); // set to blocking mode 


    if (BIO_do_accept(abio) <= 0){ // wait for connection
        fprintf(stderr, "error accepting the socket\n");
        BIO_free(abio);
        return 0;
    }

        fprintf(stderr, "Connected\n");
        printf("*Connected*\n");


    cbio = BIO_pop(abio); // retrieve BIO for connection

        unsigned char buf[512];

        buf[0] = 'M';
        buf[1] = 'W';
        buf[2] = 'X';
        buf[3] = '\n';


    if (BIO_write(cbio, buf, 512)<=0){  // write to BIO connection
        printf("FEK");
    }

    //     if (BIO_do_accept(abio) <= 0){ // wait for connection
    //     fprintf(stderr, "error accepting the socket\n");
    //     BIO_free(abio);
    //     return 0;
    // }


    BIO_free(abio);

    // BIO_free(cbio);  // Error: successive connects fail

printf("close\n");

return 0;
}

