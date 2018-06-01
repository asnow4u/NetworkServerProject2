import java.io.*;
import java.net.*;

public class FClient{
    public static void main(String[] args) throws IOException {
        
        //Variables
        String file; 
        String userCommand;
        String server;
        String host;
        int portnum;

        //Check arguments
        if (args.length < 2){
            System.out.println("Must have host name and port number as arguments\n");
            return;
        } 

        //Attept Connection
        host = args[0];
        portnum = Integer.parseInt(args[1]);
        System.out.println("Connecting to " + host + " through port " + portnum + "\n");
        
        Socket sock = new Socket(host, portnum);
        System.out.println("Connected\n");

        //Establish Connection
        PrintWriter out = new PrintWriter(sock.getOutputStream(), true); 
        BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        
        
        //Check for Arguments 3 and 4    
        if (args.length > 2){
            if ("-l".equals(args[2])){
                
                //Send for and print directory list
                out.println("Dir");
                System.out.println("Directory Files:");
                server = in.readLine();
                
                while (server != null){
                    System.out.println(server);
                    server = in.readLine();
               }
                
               return;

            } else if ("-g".equals(args[2])){
                
                //Request file
                if (args.length > 3){
                    out.println(args[3]);
                    server = in.readLine();
                    System.out.println(server);
                    
                    if ("Recieving File...".equals(server)){
                       
                        File path = new File(args[3]);
                        OutputStream writeFile = new FileOutputStream(path);
                        System.out.println("\nFile Created\n");
                        server = in.readLine();

                        while (server != null){
                             writeFile.write(server.getBytes());
                             server = in.readLine();
                        }
                        
                        writeFile.close();
                    } 

                    return;

                } else {
                   
                    System.out.print("File> ");
                    file = input.readLine();
                    
                    out.println(file);
                    server = in.readLine();
                    System.out.println(server);

                    if ("Recieving File...".equals(server)){
                        
                        File path = new File(file);
                        OutputStream writeFile = new FileOutputStream(path);
                        System.out.println("\nFile Created\n");
                        server = in.readLine();

                        while (server != null){
                            writeFile.write(server.getBytes());
                            server = in.readLine();
                        }

                        writeFile.close();
                    }

                    return;
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

            if ("-l".equals(userCommand)){
                
                //Send for and print directory
                out.println("Dir");
                System.out.println("Directory Files:");
                server = in.readLine();

                while (server != null){
                    System.out.println(server);
                    server = in.readLine();
                }

            } else if ("-g".equals(userCommand)){
                
                //Request file
                
                System.out.print("File> ");
                file = input.readLine();
                
                out.println(file);
                server = in.readLine();
                System.out.println(server);

                if ("Recieving File...".equals(server)){
                    
                    File path = new File(file);
                    OutputStream writeFile = new FileOutputStream(path);
                    System.out.println("\nFile Created\n");
                    server = in.readLine();

                    while (server != null){
                        writeFile.write(server.getBytes());
                        server = in.readLine();
                    }
                    
                    writeFile.close();
                }

                return;
                
            } else {
               
               System.out.println("Invalid Command\n");
                return;
            }
        }

    }
}
