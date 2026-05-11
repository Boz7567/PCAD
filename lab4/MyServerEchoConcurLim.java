package lab4;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class MyServerEchoConcurLim {
    private static final int PORT_NUMBER = 4244;
    public static void main(String[] args) {
        MyQueue sharedQueue = new MyQueueLim(3);

        try (ServerSocket server = new ServerSocket(PORT_NUMBER)) {
            System.out.println("Server in ascolto sulla porta " + PORT_NUMBER);
            while (true) {
                Socket socket = server.accept();
                MyServiceEcho service = new MyServiceEcho(socket, sharedQueue);
                new Thread(service).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}