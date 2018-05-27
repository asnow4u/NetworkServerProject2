#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

int main(int argc , char *argv[]){

    //Check number of arguments
    if(argc < 2){
        printf("Need a port num argument\n");
        exit(1);
    }

    int sock;
    int port = atoi(argv[1]);
    int client_sock;
    int c;
    int read_size;
    struct sockaddr_in serv_addr , client;
    char client_message[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);

    if (sock < 0){
        perror("Could not create socket");
        exit(1);
    }

    //Prepare the sockaddr_in structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( port );

    //Bind
    if( bind(sock,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        perror("Bind failed. Error");
        return 1;
    }

    //Listen
    listen(sock , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    





    //accept connection from an incoming client
    client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    




    //Receive a message from client
    while( (read_size = read(client_sock , client_message , sizeof(client_message))) > 0 )
    {
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
        memset( &client_message, 0, sizeof(client_message));
    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
    return 0;
 }
