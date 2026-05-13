import java.io.*;
import java.net.*;

public class GestoreConnessione implements Runnable {
    private static int contatoreGlobal = 0; 
    private int idMioClient;
    private Socket socket;
    private FIFO fifo;

    public GestoreConnessione(Socket socket, FIFO fifo) {
        this.socket = socket;
        this.fifo = fifo;
        synchronized(GestoreConnessione.class) {
            this.idMioClient = ++contatoreGlobal;
        }
    }

    @Override
    public void run() {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

            String tipo = in.readLine();
            if (tipo == null) return;

            if ("producer".equals(tipo)) {
                out.println("okprod");
                String messaggio;
                // Legge continuamente finché il produttore invia stringhe
                while ((messaggio = in.readLine()) != null) {
                    fifo.inserisci(messaggio);
                    out.println("okins");
                    System.out.println("Server: Produttore ha inserito un messaggio.");
                }
            } 
            else if ("consumer".equals(tipo)) {
                out.println("okcons");
                // Invia continuamente stringhe al consumatore finché la connessione è aperta
                while (true) {
                    String dato = fifo.preleva();
                    out.println("Consumer " + idMioClient + " received: " + dato);
                    System.out.println("Server: inviato dato a Consumer " + idMioClient);
                }
            }
        } catch (Exception e) {
            System.out.println("Client " + idMioClient + " disconnesso.");
        }
    }
}
