package lab4;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerEchoConcur {
    private static final int PORT_NUMBER = 4242;
    public static void main(String[] args) {
        MyQueueUnlim sharedQueue = new MyQueueUnlim();

        try (ServerSocket server = new ServerSocket(PORT_NUMBER)) {
            System.out.println("Server in ascolto sulla porta " + PORT_NUMBER);
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