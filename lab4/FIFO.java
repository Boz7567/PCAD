//implemento una classe della coda usando le linkedlist


import java.util.LinkedList;

public class FIFO {
    private final LinkedList<String> queue = new LinkedList<>();
    private final int limit;

    public FIFO(int limit) {
        this.limit = limit;
    }

    public synchronized void inserisci(String s) throws InterruptedException {
        while (limit > 0 && queue.size() == limit) {
            wait(); 
        }
        queue.addLast(s);
        notifyAll(); 
    }

    public synchronized String preleva() throws InterruptedException {
       
        while (queue.isEmpty()) {
            wait();
        }
        String s = queue.removeFirst();
        notifyAll(); 
        return s;
    }
}
