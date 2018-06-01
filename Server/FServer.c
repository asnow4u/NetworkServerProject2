#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<dirent.h>

int main(int argc , char *argv[]){

    //Check number of arguments
    if(argc < 2){
        printf("Need a port num argument\n");
        exit(1);
    }
    
    //Variables
    int sock;
    int client_sock;
    int port = atoi(argv[1]);
    struct sockaddr_in serv_addr , client;
    char client_message[256];
    int len;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    
    if (sock < 0){
        perror("Could not create socket");
        exit(1);
    }

    //Prepare the sock
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( port );

    //Bind socket 
    bind(sock,(struct sockaddr *) &serv_addr, sizeof(serv_addr)); 
    
    listen(sock, 5);
    printf("\n\nWaiting for connection...\n");

    client_sock = accept(sock, NULL, NULL);
    printf("\nConnection Established\n");

    //Recieve from client
    recv(client_sock, &client_message, sizeof(client_message), 0);
    len = strlen(client_message);
    
    if (client_message[len-1] == '\n'){
        client_message[len-1] = 0;
    }

    //Directory request (if client message == Dir
    if (strcmp("Dir", client_message) == 0){   
        
        //Send Directory to client
        struct dirent *de;
        DIR *dr = opendir(".");

        while ((de = readdir(dr)) != NULL){
            send(client_sock, de->d_name, strlen(de->d_name), 0);   
            send(client_sock, "\n", strlen("\n"), 0);
       }

        closedir(dr);

    } else {
     
        //All other request will be considered a file request.
        //The client will determain if the proper command is used. 
        FILE* file;
        file = fopen(client_message, "r");
        printf("\nChecking for %s \n", client_message); 
        
        //Check file
        if (file == NULL){
            send(client_sock, "File Not Found", strlen("File Not Found"), 0);
        } else {
            
            //Send file
            int cRead;
            unsigned char buffer[1024] = {0};
            
            printf("\nSending File...\n");
            send(client_sock, "Recieving File...\n", strlen("Recieving File...\n"), 0);
            //read from file
            cRead = fread(buffer, 1, 1024, file);
            
            //Check reading in case file is bigger than 1024 bytes.
            //Send what was aquired 
            while (cRead == 1024){
                if (cRead > 0){
                    send(client_sock, buffer, cRead, 0);
                }
            }
            
            //Send last section of file.
            //check for EOF and close file
            if (cRead < 1024){
                send(client_sock, buffer, cRead, 0);
                if (feof(file)){
                    printf("\nFile Sent\n\n");
                    fclose(file);
                }
            }  
         }
      }

    close(sock);
    return 0;
 }
