// ProducerClient.java
package lab4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class ProducerClient {
    static final int NUM_PRODUCERS = 2;

    static class ProducerTask implements Runnable {
        private final int id;

        ProducerTask(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            try {
                Socket socket = new Socket("localhost", 4242);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

                pw.println("producer");
                pw.flush();
                br.readLine(); // okprod

                pw.println("hello from producer " + id);
                pw.flush();
                System.out.println("[Producer " + id + "] server replied: " + br.readLine()); // okins

                br.close();
                socket.close();
            } catch (IOException e) {
                System.err.println("[Producer " + id + "] error: " + e.getMessage());
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread[] threads = new Thread[NUM_PRODUCERS];

        for (int i = 0; i < NUM_PRODUCERS; i++) {
            threads[i] = new Thread(new ProducerTask(i));
        }

        for (Thread t : threads) t.start();
        for (Thread t : threads) t.join();
    }
}