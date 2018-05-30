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

    int sock;
    int client_sock;
    int port = atoi(argv[1]);
    struct sockaddr_in serv_addr , client;
    char client_message[256];

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
    printf("Waiting for connection...\n");

    client_sock = accept(sock, NULL, NULL);
    printf("Connection Established\n");

    //Recieve from client
    recv(client_sock, &client_message, sizeof(client_message), 0);
    
    if (strcmp("Dir", client_message)){
        
        //Send Directory to client
        struct dirent *de;
        DIR *dr = opendir(".");

        while ((de = readdir(dr)) != NULL){
            //printf("%s\n", de->d_name);

            send(client_sock, de->d_name, strlen(de->d_name), 0);   
            send(client_sock, "\n", strlen("\n"), 0);
       }

        closedir(dr);

    } else {
        //search and send file
    }

       
    
    //client_message can be equal to "Dir", send directory, otherwise search for file and send result, either file or couldnt find file message 







    return 0;
    
 }
