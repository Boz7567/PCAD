package lab4;

import java.util.LinkedList;

public class MyQueue {

    private final LinkedList<String> queue;

    public MyQueue(){
        queue = new LinkedList<>();
    }

    public synchronized void push(String val) throws InterruptedException {

        queue.addLast(val);

        notifyAll();
    }

    public synchronized String pop() throws InterruptedException {
        
        while(queue.isEmpty()) wait();

        return queue.removeFirst();
    }
}