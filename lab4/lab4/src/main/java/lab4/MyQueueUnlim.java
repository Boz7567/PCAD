package lab4;

import java.util.LinkedList;

public class MyQueueUnlim implements MyQueue{

    protected final LinkedList<String> queue;

    public MyQueueUnlim(){
        queue = new LinkedList<>();
    }

    @Override
    public synchronized void push(String val) throws InterruptedException {

        queue.addLast(val);

        notifyAll();
    }

    @Override
    public synchronized String pop() throws InterruptedException {
        
        while(queue.isEmpty()) wait();

        return queue.removeFirst();
    }
}