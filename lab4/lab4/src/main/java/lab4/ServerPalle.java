package lab4;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.LinkedBlockingQueue;
public class ServerPalle implements Runnable{
    private static final LinkedBlockingQueue<String> FIFO = new LinkedBlockingQueue<>();
    private ServerSocket server;
    @Override
    public void run() {
        try{
            this.server = new ServerSocket(4242);
            while (true) { 
                Socket socket = server.accept();
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
                String str = br.readLine();
                // do stuff
                switch (str) {
                    case "producer":
                        pw.println("okprod");
                        str = br.readLine();
                        FIFO.put(str);
                        break;
                    case "consumer":
                        pw.println("okcons");
                        if(FIFO.isEmpty()){
                            //wait code here
                        }
                        str = FIFO.remove();
                        pw.println(str);
                    default:
                        pw.println("unexpected string recieved");
                }
                pw.flush();
                br.close();
                pw.close();
                socket.close();
            }
        } catch (Exception e) {
            System.out.println(e);
            e.printStackTrace();
        }
    }
}