#include<stdio.h>
#include<openssl/ssl.h>
#include<openssl/bio.h>

int main()
{   

    bioClient();
    // sslClient();

return 0;
}

void readBIO(BIO * bio){


    unsigned char buf[512];


    // if (BIO_read(bio,buf,512)>0){
    //     printf(buf);
    // }
    // else{

    //     buf[0] = 'f';
    //     buf[1] = 'e';
    //     buf[2] = 'k';
    //     buf[3] = '\n';

    //     printf(buf);
    // }
            printf("read start");

           while(BIO_read(bio,buf,sizeof(buf)) > 0){
               printf("%s",buf);
               if (BIO_eof(bio) == 1)
                    break;
            }

            printf("read end");
    return;
}

void sslClient()
{


    SSL_load_error_strings();
    SSL_library_init();

    SSL_CTX *ctx;
    SSL *ssl;
    BIO *bio;

    fprintf(stderr,"1");
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) {
      printf("failed to create the SSL context\n");
      return;
    }

    if(!SSL_CTX_load_verify_locations(ctx, "cert.crt", NULL)){
	    printf("Certificate failed");
	    return 0;
    }

    fprintf(stderr,"2");

    bio = BIO_new_ssl_connect(ctx);
    if (bio == NULL){
        printf("failed retrieving the BIO object \n");
    }

    BIO_get_ssl(bio,&ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    fprintf(stderr,"3");

    BIO_set_conn_hostname(bio,"localhost:6969");


    if (BIO_do_connect(bio) <= 0){
        fprintf(stderr,"fek");
        return;
    }


        fprintf(stderr,"4");


    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
        fprintf(stderr, "Certificate verification error: %li\n", SSL_get_verify_result(ssl));
        return ;
    }



    fprintf(stderr,"5");

    readBIO(bio);

    BIO_free(bio);

}


void bioClient()
{

    BIO *cbio;

    SSL_library_init();

    cbio = BIO_new_connect("localhost:6969");

    if (BIO_do_connect(cbio) <= 0){
        printf("fek");
        return;
    }

    readBIO(cbio);

    BIO_free_all(cbio);






}