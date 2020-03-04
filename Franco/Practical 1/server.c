#include<stdio.h>
#include<openssl/ssl.h>
#include<openssl/bio.h>



int main()
{




    bioServer();    // BIO
    // sslServer();    //   SSL



    return 0;
}


void sslServer()
{   

    SSL_load_error_strings();
    SSL_library_init();

    SSL_CTX *ctx;
    SSL *ssl;

    BIO *bio, *abio, *cbio;

    ctx = SSL_CTX_new(SSLv23_server_method());
    if (ctx == NULL){
        fprintf(stderr,"failed to create the SSL context\n");
        return;
    }

        /*Loads and verifies the certificate and the key*/
    if(SSL_CTX_use_certificate_file(ctx,"webServCert.crt", SSL_FILETYPE_PEM) <= 0){
	    fprintf(stderr,"Certificate failed");
	    return;
    }
    
    if (SSL_CTX_use_PrivateKey_file(ctx,"webServ.key",SSL_FILETYPE_PEM) <= 0) {
	    fprintf(stderr,"Key failed");
            return;
    }

    if (SSL_CTX_check_private_key(ctx) <= 0) {
        fprintf(stderr,"Key ");
        return;
    }


    bio = BIO_new_ssl(ctx,0);
    if (bio == NULL){
        fprintf(stderr,"failed retrieving the BIO object \n");
    }



    BIO_get_ssl(bio,&ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);



    abio = BIO_new_accept("6969");  
    BIO_set_accept_bios(abio,bio);

    if (BIO_do_accept(abio) <= 0){ // wait for connection
        fprintf(stderr, "error accepting the socket\n");
        BIO_free(abio);
        return;
    }
  

    BIO_set_nbio_accept(abio,0); // set to blocking mode 


    if (BIO_do_accept(abio) <= 0){ // wait for connection
        fprintf(stderr, "error connecting the socket\n");
        BIO_free(abio);
        return;
    }

        fprintf(stderr, "Connected\n");

        cbio = BIO_pop(abio); // retrieve BIO for connection
        
        if (BIO_do_handshake(cbio) <= 0){
            printf("handshake failed\n");
            return;
        }
        else{
            printf("handshake passed\n");
        }

        unsigned char buf[512];

        buf[0] = 'B';
        buf[1] = 'O';
        buf[2] = 'B';
        buf[3] = '\n';

        readBIO(cbio);
        BIO_puts(cbio, "HTTP/1.1 200 OK\r\n\r\n\r\n");
        


     if (write_page(cbio,"MainPage.html") <= 0)
        printf("fek");

            // BIO_flush(cbio);
        //  BIO_free_all(cbio);

    BIO_free_all(abio);

    return;
}

void bioServer()
{
        // write_text("bob.txt");

    SSL_library_init();

    BIO *abio, *cbio;

    abio = BIO_new_accept("6969"); // new listening BIO


    if (BIO_do_accept(abio) <= 0){  // set up socket
        fprintf(stderr, "error setting up the listening socket\n");
        BIO_free(abio);
        return;
    }

    BIO_set_nbio_accept(abio,0); // set to blocking mode 


    if (BIO_do_accept(abio) <= 0){ // wait for connection
        fprintf(stderr, "error accepting the socket\n");
        BIO_free(abio);
        return;
    }

        fprintf(stderr, "Connected\n");
        printf("*Connected*\n");


    cbio = BIO_pop(abio); // retrieve BIO for connection



        unsigned char buf[512];

        buf[0] = 'B';
        buf[1] = 'O';
        buf[2] = 'B';
        buf[3] = '\n';


     if (write_page(cbio,"MainPage.html") <= 0)
        printf("fek");
    // if (BIO_write(cbio, buf, 512)<=0){  // write to BIO connection
    //     printf("FEK");
    // }

    BIO_flush(cbio);

        while(1){
        
    }

    BIO_free_all(abio);

    // BIO_free(cbio);  //  Error: successive connects fail

printf("close\n");

return;
}

void readBIO(BIO * bio){


    unsigned char buf[512];


    if (BIO_read(bio,buf,512)>0){
        fprintf(stderr, buf);
    }
    else{

        buf[0] = 'f';
        buf[1] = 'e';
        buf[2] = 'k';
        buf[3] = '\n';

        fprintf(stderr, buf);
    }


    return;
}




// A simple function that reads a text file and writes it to the BIO object is shown below. Thisfunction is trivial and will not be explained.

int write_page(BIO * bio, const char * page){

    FILE * f;
    int bytesread = 0;
    unsigned char buf[512];

    f = fopen(page,"r");

    if (!f){
        printf("could not open the page\n");
        return 0;
    }


    while(1){

        bytesread = fread(buf,sizeof(unsigned char),512,f);

        if (bytesread == 0){
            printf("page end");
            break;
        }

        if (BIO_write(bio, buf, bytesread)<=0){  // write to BIO connection
            printf("Write failed \n");
            break;
        }


    }

    fclose(f);



    return 1;
}