package lab4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class MyServiceEcho implements Runnable {

    private final MyQueue fifo;
    private final Socket socket;

    public MyServiceEcho(Socket socket, MyQueue fifo) {
        this.socket = socket;
        this.fifo = fifo;
    }

    @Override
    public void run() {
        try (
            BufferedReader br = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));

            PrintWriter pw = new PrintWriter(
                new OutputStreamWriter(socket.getOutputStream()));
        ) {

            String line = br.readLine();

            if (line == null) return;

            switch (line) {

                case "producer": {
                    pw.println("okprod");
                    pw.flush();

                    String data = br.readLine();

                    if (data != null) {
                        fifo.push(data);

                        pw.println("okins");
                        pw.flush();
                    }
                    break;
                }

                case "consumer": {
                    pw.println("okcons");
                    pw.flush();

                    String data = fifo.pop();

                    pw.println(data);
                    pw.flush();
                    break;
                }

                default: {
                    pw.println("unexpected string received");
                    pw.flush();
                    break;
                }
            }

        } catch (IOException | InterruptedException e) {
            System.err.println(e.getMessage());

        } finally {
            try {
                socket.close();
            } catch (IOException e) {
            }
        }
    }
}