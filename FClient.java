import java.io.*;
import java.net.*;

public class FClient{
    public static void main(String[] args) throws IOException {
        
        String file; 
        String userCommand;

        //Check arguments
        if (args.length < 2){
            System.out.println("Must have host name and port number as arguments\n");
            return;
        } 

        //Attept Connection
        String host = args[0];
        int portnum = Integer.parseInt(args[1]);
        System.out.println("Connecting to " + host + " through port " + portnum + "\n");
        Socket sock = new Socket(host, portnum);
        System.out.println("Connected\n");

        //Establish Connection
        PrintWriter out = new PrintWriter(sock.getOutputStream(), true); 
        BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        
        
        //Check for Arguments 3 and 4    
        if (args.length > 2){
            if ("-1".equals(args[2])){
                //Directory
                out.write("Directory"); 
            } else if ("-g".equals(args[2])){
                //File
                if (args.length > 3){
                    //fetch file
                } else {
                    System.out.print("File> ");
                    file = input.readLine();
                    //fetch file
                }
           
            } else {
                //Invalid command
                System.out.println("Invalid Command\n");
                return;
            }
        
        //If argument 3 and 4 were not provided, ask user for them
        } else {
            System.out.print("Command> ");
            userCommand = input.readLine();
            if ("-1".equals(userCommand)){
                //directory
            } else if ("-g".equals(userCommand)){
                //File
                System.out.print("File> ");
                file = input.readLine();
                //fetch file
            } else {
                System.out.println("Invalid Command\n");
                return;
            }
        }

             








    }
}
