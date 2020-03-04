#include<stdio.h>
#include<openssl/ssl.h>
#include<openssl/bio.h>

char* certificateFileName;


int main(int argc, char* argv[])
{
    // bioClient();
    certificateFileName = argv[1];


    sslClient();

return 0;
}


/**
 * @brief This function makes a connection to the web server and presents the used with
 * a simply UI. It allows them to navigate to different pages and to download files.
 * The UI will continue to be presented to the user until the client fails to make a connection
 * to the web server or until the user decides to close the client.
 */
void sslClient()
{
    SSL_load_error_strings();
    SSL_library_init();     ///load cipher and hash algorithms

    SSL_CTX *context;
    SSL *sslObject;
    BIO *bioObject;

    char replyBuffer[512];      ///this holds the data sent from the webserver

    fprintf(stderr,"1");
    context = SSL_CTX_new(SSLv23_client_method());
    if (context == NULL) {
      printf("failed to create the SSL context\n");
      return;
    }

    if(!SSL_CTX_load_verify_locations(context, certificateFileName, NULL)){
	    printf("Certificate failed");
	    return 0;
    }

    fprintf(stderr,"2");

    bioObject = BIO_new_ssl_connect(context);
    if (bioObject == NULL){
        printf("failed retrieving the BIO object \n");
    }

    BIO_get_ssl(bioObject,&sslObject);
    SSL_set_mode(sslObject, SSL_MODE_AUTO_RETRY);

    fprintf(stderr,"3");

    BIO_set_conn_hostname(bioObject,"localhost:6969");


    if (BIO_do_connect(bioObject) <= 0){
        fprintf(stderr,"fek\n");
        return;
    }


    fprintf(stderr,"4");


    if(SSL_get_verify_result(sslObject) != X509_V_OK)
    {
        fprintf(stderr, "Certificate verification error: %li\n", SSL_get_verify_result(sslObject));
        return ;
    }



    fprintf(stderr,"5");

    fprintf(stderr, "Connection established.\n");

    int function = -1;

    while (function != 6)
    {
        printf("\n\n==========================================================\n");
        printf("Enter the number of your choice:\n");
        printf("1: Load the default page.\n");
        printf("2: Go to Notflix.\n");
        printf("3: Go to Spotafly.\n");
        printf("4: Go to Prawnhub.\n");
        printf("5: Download a file.\n");
        printf("6: Disconnect.\n");
        printf("==========================================================\n");
        printf(">");

        scanf("%d", &function); //get the response from the user

        switch (function)
        {
        case 1:
            printf("\nRequesting default page.\n\n");
            BIO_write(bioObject, "Website/Default_Page.html", 512); ///send file we want to get
            while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
            { ///read the reply and print it out
                printf("%s", replyBuffer);
                if (BIO_eof(bioObject) == 1){
                    break;
                }
                
                char* index = strchr(replyBuffer, '\0');
                if (index != NULL){
                    break;
                }
            }
            break;
        case 2:
            printf("\nRequesting Notflix.\n\n");
            BIO_write(bioObject, "Website/Notflix.html", 512); ///send file we want to get
            while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
            { ///read the reply and print it out
                printf("%s", replyBuffer);
            }
            printf("\n");
            break;
        case 3:
            printf("\nRequesting Spotafly.\n\n");
            BIO_write(bioObject, "Website/Spotafly.html", 512); ///send file we want to get
            while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
            { ///read the reply and print it out
                printf("%s", replyBuffer);
            }
            printf("\n");
            break;
        case 4:
            printf("\nRequesting Prawnhub.\n\n");
            BIO_write(bioObject, "Website/Prawn_Hub.html", 512); ///send file we want to get
            while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
            { ///read the reply and print it out
                printf("%s", replyBuffer);
            }
            printf("\n");
            break;
        case 5:
            printf("\nWhich file do you want to download?\n\n");
            // printf("1. ted.pdf\n");
            printf("1. ratatouille_script.pdf\n");
            printf("2. 21_Jump_Street.pdf\n");
            printf("3. crabRave.mp3\n");
            printf("4. flySound.mp3\n");
            printf("5. noice.mp3\n");
            printf("6. PrawnHub.png\n");
            printf("7. PrawnsInParadise.jpg\n");
            printf(">");
            int fileNumber = -1;

            FILE * fileDownload;
            char* filename;

            scanf("%d", &fileNumber);

            switch (fileNumber)
            {
            case 9:
                filename = "Website/ted.pdf";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("ted.pdf", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                
                break;
            case 1:
                filename = "Website/ratatouille_script.pdf";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("ratatoullie_script.pdf", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            case 2:
                filename = "Website/21_Jump_Street.pdf";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("21_Jump_Street.pdf", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            case 3:
                filename = "Website/crabRave.mp3";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("crabRave.mp3", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            case 4:
                filename = "Website/flySound.mp3";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("flySound.mp3", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            case 5:
                filename = "Website/noice.mp3";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("noice.mp3", "w");

                int b = 10;
                while (b > 0)
                {
                    b = BIO_read(bioObject, replyBuffer, sizeof(replyBuffer));
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            case 6:
                filename = "Website/PrawnHub.png";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("PrawnHub.png", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            case 7:
                filename = "Website/PrawnsInParadise.jpg";
                printf("\nAttempting to download: ");
                printf(filename);
                printf("\n");
                
                BIO_write(bioObject, filename, 512);

                fileDownload = fopen("PrawnsInParadise.jpg", "w");

                while (BIO_read(bioObject, replyBuffer, sizeof(replyBuffer)) > 0)
                {
                    fwrite(replyBuffer, sizeof(unsigned char), sizeof(replyBuffer), fileDownload);
                }

                printf("Download finished.\n\n");
                break;
            default:
                printf("Invalid choice entered. Please try again.\n");
                break;
            }


            break;
        case 6:
            printf("\nDisconnecting from server and closing client.\n\n");
            BIO_free_all(bioObject);
            SSL_CTX_free(context);
            return;
            break;
        default:
            printf("\nInvalid input received. Try again.\n\n");
            break;
        }

        // printf("Finished with the switch statement.\n");
        /// Reconnect after the successful transaction

        BIO_free_all(bioObject);
        BIO_reset(bioObject);
        // if (BIO_free(bioObject) == 1)
        // {
        //     printf("Successfully freed bioObject.\n");
        // }

        // printf("Freed BIO and make new connection.\n");

        bioObject = NULL;

        bioObject = BIO_new_ssl_connect(context);

        // printf("Made new bio object using existing context.\n");
        if (bioObject == NULL)
        {
            printf("Failed to retrieve the BIO object\n");
            return;
        }

        ///disable retries like in the practical guide
        BIO_get_ssl(bioObject, &sslObject);
        SSL_set_mode(sslObject, SSL_MODE_AUTO_RETRY);

        BIO_set_conn_hostname(bioObject, "localhost:6969");
        // printf("Make connection to localhost:6969\n");

        if (BIO_do_connect(bioObject) != 1)
        {
            printf("Reconnection failed.\n");
            BIO_free_all(bioObject);
            SSL_CTX_free(context); //free both
            return;
        }

        if (SSL_get_verify_result(sslObject) != X509_V_OK)
        {
            fprintf(stderr, "Error verifying certificate.\n");
            BIO_free_all(bioObject);
            SSL_CTX_free(context);
            return;
        }
    }
}
