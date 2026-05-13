import java.io.*;
import java.net.*;

public class ClientProd {
    public static void main(String[] args) {
        try (Socket s = new Socket("localhost", 4242);
             PrintWriter out = new PrintWriter(s.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()))) {

            out.println("producer");
            if ("okprod".equals(in.readLine())) {
                for (int i = 1; i <= 10; i++) {
                    String msg = "Messaggio numero " + i + " da Produttore 3";
                    out.println(msg);
                    if ("okins".equals(in.readLine())) {
                        System.out.println("Inviato: " + i);
                    }
                    Thread.sleep(500); // Piccola pausa per vedere il limite in azione
                }
            }
        } catch (Exception e) { e.printStackTrace(); }
    }
}
