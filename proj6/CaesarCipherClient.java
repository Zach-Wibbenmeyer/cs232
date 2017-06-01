/*
 * Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 6
 * CaesarCipher Client class
 */

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class CaesarCipherClient {
    //client start point
    public static void main(String[] args) throws IOException {

        if (args.length != 2) {
            System.out.println("ERROR - wrong number of arguments...");
            return;
        }

        String tmp = "testing";

        Integer portNumber;
        String server = args[0];

        try {
            portNumber = Integer.parseInt(args[1]);
        } catch (NumberFormatException ex) {
            System.out.println("ERROR - The second value must be a valid port");
            return;
        }

        System.out.println("Welcome to the CaeserCipher service. Please enter and integer between 1 and 25: ");

        Scanner scan = new Scanner(System.in);
        Integer offset = scan.nextInt();

        // connect to the server
        Socket mySocket = new Socket(server, portNumber);

        OutputStream os = mySocket.getOutputStream();
        PrintWriter out = new PrintWriter(os);

        out.append(offset.toString()).append("\n");
        out.flush();

        BufferedReader input = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));
        String answer = input.readLine();

        if (!answer.equals(offset.toString())) {
            System.out.println("ERROR - The server returned: " + answer);
            return;
        }

        encryptUserInput(out, scan, input);
    }


    private static void encryptUserInput(PrintWriter out, Scanner scan, BufferedReader input) throws IOException {
        String answer;
        scan.nextLine();
        while(true) {
            System.out.println("Please enter the string to encrypt: ");
            String unencryptedString = scan.nextLine();

            if (unencryptedString.equals("quit")) {
                System.out.println("Thanks for using the CaesarCipher service!");
                return;
            }

            out.append(unencryptedString).append("\n");
            out.flush();

            answer = input.readLine();
            System.out.println("The encypted string is: " + answer);
        }
    }

}
