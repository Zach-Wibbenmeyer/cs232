/*
 * Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 6
 * CaesarCipher Server class
 */

import java.net.Socket;
import java.net.ServerSocket;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.concurrent.*;

public class CaesarCipherServer {

    public static void main(String[] args) throws Exception {

        ExecutorService threadPool = Executors.newFixedThreadPool(8);

        // create a socket for the server
        int PORT = 4444;
        ServerSocket ss = new ServerSocket(PORT);
        System.err.println("Started server on port " + PORT);

        // wait for connections
        while (true) {
            Socket clientSocket = ss.accept();
            ConnectionCallable connection = new ConnectionCallable(clientSocket);
            threadPool.submit(connection);
        }
    }

    private static class ConnectionCallable implements Callable<Integer>
    {
        private Socket clientSocket;

        public ConnectionCallable(Socket socketConnection) {
            this.clientSocket = socketConnection;
        }

        public Integer call() throws Exception {
            Boolean firstInput = true;
            Integer cipherNumber = 0;
            System.err.println("Accepted connection from client");

            // open up IO streams
            BufferedReader in  = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream os = clientSocket.getOutputStream();
            PrintWriter out = new PrintWriter(os);


            // waits for data and reads it in until connection dies
            String temp;
            while ((temp = in.readLine()) != null) {
                if (firstInput) {
                    try {
                        cipherNumber = Integer.parseInt(temp);
                        out.append(cipherNumber.toString()).append("\n").flush();
                        firstInput = false;
                        continue;
                    } catch (NumberFormatException ex) {
                        out.append("1st input must be an integer 1-25").flush();
                        break;
                    }
                }

                out.append(createCipher(temp, cipherNumber)).append("\n").flush();
            }

            // close the IO and socket streams
            System.err.println("Closing connection with client");
            out.close();
            in.close();
            clientSocket.close();
            return 0;
        }
    }

    /*
     * createCipher() - ciphers a String
     * @param: temp (type -> String), cipherNumber (type -> Integer)
     * @return: a cipher String
     */
    private static String createCipher(String temp, Integer cipherNumber) {
        String cipheredString = "";
	    for(int i = 0; i < temp.length(); i++) {
            char c = (char)(temp.charAt(i) + cipherNumber);
		    if (c > 'z') {
			    cipheredString += (char)(temp.charAt(i) - (26 - cipherNumber));
		    }
		    else {
			    if (Character.isLetter(c)) {
				    cipheredString += c;
			    } else {
				    cipheredString += temp.charAt(i);
			    }
		    }
	   }

	   return cipheredString;
    }
}
