import java.net.*;

public class ServerUnlimited {
    public static void main(String[] args) {
        int porta = 4242;
        FIFO SharedQueue = new FIFO(0); 

        try (ServerSocket serverSocket = new ServerSocket(porta)) {
            System.out.println("Server in ascolto sulla porta " + porta);
            
            while (true) {
                Socket clientSocket = serverSocket.accept();
                new Thread(new GestoreConnessione(clientSocket, SharedQueue)).start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
