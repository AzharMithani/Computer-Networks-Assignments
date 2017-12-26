package MultiUserChat;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/*
 * The server as a GUI
 */
public class ServerGUI implements ActionListener {
	
	
	JFrame frame;
	// the stop and start buttons
	private JButton stopStart;
	// JTextArea for the chat room and the events
	private JTextArea chat;
	// The port number
	private JTextField tPortNumber;
	// my server
	private Server server;
	
	
	// server constructor that receive the port to listen to for connection as parameter
	ServerGUI(int port) {
		frame=new JFrame("Chat Server");
		frame.setBounds(100,100,400, 400);
		frame.addWindowListener(new WindowAdapter(){  
            public void windowClosing(WindowEvent e) {  
            	if(server != null) {
        			try {
        				server.stop();			// ask the server to close the conection
        			}
        			catch(Exception eClose) {
        			}
        			server = null;
        		}
        		// dispose the frame
        		frame.dispose();
        		System.exit(0);
            }  
        });  
		frame.setLayout(null);
		server = null;
		// in the NorthPanel the PortNumber the Start and Stop buttons
		
		JLabel l1=new JLabel("Port number: ");
		l1.setBounds(10,10,100,30);
		frame.add(l1);
		
	
		tPortNumber = new JTextField(""+port);
		tPortNumber.setBounds(100,10,100,30);
		frame.add(tPortNumber);
		// to stop or start the server, we start with "Start"
		stopStart = new JButton("Start");
		stopStart.setBounds(230,10,100,30);
		stopStart.addActionListener(this);
		frame.add(stopStart);
		
		// the event and chat room
		chat = new JTextArea(80,80);
		chat.setBounds(5,45,375,310);
		chat.setEditable(false);
		appendRoom("Chat room.\n");
		frame.add(chat);
		
		
		
		frame.setVisible(true);
	}		

	// append message to the two JTextArea
	// position at the end
	void appendRoom(String str) {
		chat.append(str);
		chat.setCaretPosition(chat.getText().length() - 1);
	}
	
	
	// start or stop where clicked
	public void actionPerformed(ActionEvent e) {
		// if running we have to stop
		if(server != null) {
			server.stop();
			server = null;
			tPortNumber.setEditable(true);
			stopStart.setText("Start");
			return;
		}
      	// OK start the server	
		int port;
		try {
			port = Integer.parseInt(tPortNumber.getText().trim());
		}
		catch(Exception er) {
			System.out.println("Invalid port number");
			return;
		}
		// ceate a new Server
		server = new Server(port, this);
		// and start it as a thread
		new ServerRunning().start();
		stopStart.setText("Stop");
		tPortNumber.setEditable(false);
	}
	
	// entry point to start the Server
	public static void main(String[] arg) {
		// start server default port 1500
		new ServerGUI(1500);
	}

	/*
	 * If the user click the X button to close the application
	 * I need to close the connection with the server to free the port
	 */
	
	class ServerRunning extends Thread {
		public void run() {
			server.start();         // should execute until if fails
			// the server failed
			stopStart.setText("Start");
			tPortNumber.setEditable(true);
			System.out.println("Server crashed\n");
			server = null;
		}
	}

}
