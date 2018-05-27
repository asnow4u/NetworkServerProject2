import java.io.*;
import java.net.*;

public class FClient{
    public static void main(String[] args) throws IOException {
        
        //Check number of arguments
        //if (args.length != 

        String host = args[0];
        int portnum = Integer.parseInt(args[1]);
        Socket sock = new Socket(host, portnum);
        PrintWriter out = new PrintWriter(sock.getOutputStream(), true); 
        BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        BufferedReader stdln = new BufferedReader(new InputStreamReader(System.in));
        


        String userInput;

        








    }
}
