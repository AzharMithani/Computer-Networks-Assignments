package TCP_UDP_Chat;

/**
 *
 * @author azhar
 */
import java.io.*;
import java.net.*;

public class TCP_Server
{
	public static void main(String args[]) throws IOException
	{
		ServerSocket ss = null;
		Socket socket =null;
			
		String message = null;
		
		ss = new ServerSocket(8002);
		System.out.println("Server socket is created and waiting for client");
		DataOutputStream ostream;
                DataInputStream istream;
                socket = ss.accept();
               
				
		ostream = new DataOutputStream(socket.getOutputStream());
		istream = new DataInputStream(socket.getInputStream());
		

		message = istream.readUTF();

		System.out.println("Client Says: "+message);
			
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
		System.out.println("Enter Server Message:");
		message = br.readLine();

		ostream.writeUTF(message);

		System.out.println("Reply to Client:" +message);
               
		
               
                socket.close();
		ostream.close();
		istream.close();
	}
}


