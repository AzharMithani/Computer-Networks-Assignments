package TCP_UDP_Chat;

/**
 *
 * @author azhar
 */
import java.io.*;
import java.net.*;

public class TCP_Client
{
	public static void main(String args[]) throws IOException
	{
		
		Socket cs = null;
			
		String message = null;
		DataOutputStream ostream;
                DataInputStream istream;
		//cs = new Socket("172.21.20.4",8001);
                cs = new Socket(InetAddress.getLocalHost(),8002);
                System.out.println("Client socket is created and waiting for server");
                
                                                  
			
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
		System.out.println("Enter Client Message:");
		message = br.readLine();
		
		ostream = new DataOutputStream(cs.getOutputStream());
		istream = new DataInputStream(cs.getInputStream());
		
		ostream.writeUTF(message);
		ostream.flush();
	message = istream.readUTF();
		
		System.out.println("Client Says: "+message);
		
        
		cs.close();
		ostream.close();
		istream.close();
	}
}