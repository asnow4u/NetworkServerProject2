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
    printf("Waiting for connection...\n");

    client_sock = accept(sock, NULL, NULL);
    printf("Connection Established\n");

    //Recieve from client
    recv(client_sock, &client_message, sizeof(client_message), 0);
    len = strlen(client_message);
    if (client_message[len-1] == '\n'){
        client_message[len-1] = 0;
    }

    if (strcmp("Dir", client_message) == 0){ //If client message = Dir  
        //Send Directory to client
        struct dirent *de;
        DIR *dr = opendir(".");

        while ((de = readdir(dr)) != NULL){
            send(client_sock, de->d_name, strlen(de->d_name), 0);   
            send(client_sock, "\n", strlen("\n"), 0);
       }

        closedir(dr);

    } else {
        
        FILE* file;
        
        //int len;
        //len = strlen(client_message);
        //if( client_message[len-1] == '\n'){
        //    client_message[len-1] = 0;
        //   
        //  }

        
        file = fopen(client_message, "r");
        if (file == NULL){
            printf("Failed to open file");
        } else {
            printf("Opened file");
        }

    }

       
    







    return 0;
    
 }
