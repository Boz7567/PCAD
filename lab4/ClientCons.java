import java.io.*;
import java.net.*;

public class ClientCons {
    public static void main(String[] args) {
        try (Socket s = new Socket("localhost", 4242);
             PrintWriter out = new PrintWriter(s.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()))) {

            out.println("consumer");
            if ("okcons".equals(in.readLine())) {
                System.out.println("Consumatore pronto a ricevere tutto...");
                String ricevuto;
                // Resta nel ciclo finché il server invia dati
                while ((ricevuto = in.readLine()) != null) {
                    System.out.println(ricevuto);
                }
            }
        } catch (Exception e) { e.printStackTrace(); }
    }
}
