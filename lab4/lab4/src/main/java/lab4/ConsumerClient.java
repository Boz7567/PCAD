package lab4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class ConsumerClient {
    public static void main(String[] args) {
        String host = "localhost";
        int port = 4242;

        try {
            Socket socket = new Socket(host, port);
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
            pw.println("consumer");
            pw.flush();

            String response = br.readLine();
            System.out.println("Server: " + response);

            System.out.println("Waiting for a message...");
            String message = br.readLine();
            System.out.println("Received: " + message);

        } catch (IOException e) {
            System.err.println("Connection error: " + e.getMessage());
        }
    }
}