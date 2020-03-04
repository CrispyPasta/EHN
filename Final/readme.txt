server.c usage:
1. Open a terminal in the Server folder.
2. In the command line, enter "make" to compile the code.
3. In the command line, enter "make run" to run the code with the generated certificate and key files. 
3.1 Alternatively, enter the filename of the certificate or key files you would like to use. 

client.c usage:
1. Open a terminal in the Client folder.
2. In the command line, enter "make" to compile the code.
3. In the command line, enter "make tun" to run the client program using the generated certificate.
4. You will be presented with a choice of content. Make your choice by entering the number corresponding to the content you would like
   to see and hitting the return key. 
4.1 If you chose to go to a certain web page, the html for that page will be displayed. 
4.2 If you chose to download a file, the file will be downloaded to the Client folder. 
5. To close the client, choose option number 7 when asked what you would like to do. 
6. To enter a custom request, choose option number 6. Upon being prompted, enter the request you want to send to the server. 