// ConsumerClient.java
package lab4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class ConsumerClient {
    static final int NUM_CONSUMERS = 5;

    static class ConsumerTask implements Runnable {
        private final int id;

        ConsumerTask(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            try {
                Socket socket = new Socket("localhost", 4242);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

                pw.println("consumer");
                pw.flush();
                br.readLine(); // okcons

                System.out.println("[Consumer " + id + "] received: " + br.readLine());

                br.close();
                socket.close();
            } catch (IOException e) {
                System.err.println("[Consumer " + id + "] error: " + e.getMessage());
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread[] threads = new Thread[NUM_CONSUMERS];

        for (int i = 0; i < NUM_CONSUMERS; i++) {
            threads[i] = new Thread(new ConsumerTask(i));
        }

        for (Thread t : threads) t.start();
        for (Thread t : threads) t.join();
    }
}