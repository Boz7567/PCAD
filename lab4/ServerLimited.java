import java.net.*;

public class ServerLimited {
    public static void main(String[] args) {
        int porta = 4242;
        FIFO buffer = new FIFO(5); // Limite di 5 elementi
        try (ServerSocket server = new ServerSocket(porta)) {
            System.out.println("Server pronto sulla porta " + porta);
            while (true) {
                Socket s = server.accept();
                new Thread(new GestoreConnessione(s, buffer)).start();
            }
        } catch (Exception e) { e.printStackTrace(); }
    }
}
