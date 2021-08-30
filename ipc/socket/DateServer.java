import java.net.*;
import java.io.*;

public class DateSever {
	public static void main(String[] args) throws Exception {
		ServerSocket server = new ServerSocket(6013);
		/* Now listen for connections */
		while (true) {
			System.out.println("Listening...");
			Socket client = server.accept();
			PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
			System.out.println("New Client is connected ...");
			/* write the Date to the socket */
			pout.println(new java.util.Date().toString());
			/* close the socket and resume listening for connctions */
			client.close();
		}
	}
}