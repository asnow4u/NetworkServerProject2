Welcome to a File transfer system. If the server has a file that you want on your client, this program is what you need.

There are two folder within the zip file that contain the server and client. There are pre compiled programs there but can be compiled with the following code.

javac FClient.java
gcc FServer.c -o server

You will need to run the two files in two separate terminals.

The programs can be ran using the following files with the code below.

Concerning the server, you need to supply a PortNumber you want the server to be on.

./server PortNumber

This will start your server. As long as the PortNumber you supplied is an open port, the server will wait for a connection from the client.

Now to the client. In a new terminal, get to the file where the FClient was
compiled then run the below code to run the program. You will need to provide a Hostname(localhost) and the same PortNumber for the server. 

java FClient hostname PortNumber

You may also add more arguments after portnumber if you know what you are looking for. If not the console will ask for your input.

The client needs a command which can be 
-l  for a list of files on the server 
-g  to be able to get a file from the server

(java FClient hostname portnumber command)

If you use the command -g you can provide a file name argument you want to grab from the server
(java FClient hostname portnumber filename)

If you do not provide a file name the terminal will ask you for one.

The server will send your request back and display it on the client terminal based upon the command given.  
 
 If you ask for a file and it displays that file was created, the file will be found in the folder where you compiled the client. use "ls" to see the files in the directory.   

