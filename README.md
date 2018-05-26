Welcome to a simple chat system between two different terminals. You will need
to compile the server code and client code using the following commands in a
terminal.

javac ChatServer.java
g++ ChatClient.cpp -o ChatClient

This will create two files that you will need to run in two separate terminals.
Run the following files with the code below.

Concerning the server, you need to supply a PortNumber you want the server to be
on.

java ChatServer PortNumber

This will start your server. As long as the PortNumber you supplied is a open
port, the server will wait for a connection from the client.

Now to the client. In a new terminal, get to the file where the ChatClient was
compiled then run the below code to run the program. You will need to provide a
Hostname and the same PortNumber for the server.

./ChatClient hostname PortNumber

You should have both client and server up and they should be ready to communicate.
Type any message and press enter. Then move to the server and respond. Continue
till you are done with your conversation.

Exit by typing "quit" and pressing enter.

Have fun!!!
