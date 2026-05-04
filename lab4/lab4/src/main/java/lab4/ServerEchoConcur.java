package lab4;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.LinkedBlockingQueue;

public class ServerEchoConcur {
    public static void main(String[] args) {
        LinkedBlockingQueue<String> sharedQueue = new LinkedBlockingQueue<>();

        try (ServerSocket server = new ServerSocket(4242)) {
            System.out.println("Server in ascolto sulla porta 4242...");
            while (true) {
                Socket socket = server.accept();
                ServiceEcho service = new ServiceEcho(socket, sharedQueue);
                new Thread(service).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}