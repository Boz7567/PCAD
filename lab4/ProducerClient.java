package lab4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ProducerClient {
    public static void main(String[] args) {
        String host = "localhost";
        int port = 4244;

        try {
            Socket socket = new Socket(host, port);
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
            Scanner scanner = new Scanner(System.in);

            pw.println("producer");
            pw.flush();

            String response = br.readLine();
            System.out.println("Server: " + response);

            System.out.print("Enter string to send: ");
            String message = scanner.nextLine();

            pw.println(message);
            pw.flush();

            response = br.readLine();
            System.out.println("Server: " + response);

        } catch (IOException e) {
            System.err.println("Connection error: " + e.getMessage());
        }
    }
}