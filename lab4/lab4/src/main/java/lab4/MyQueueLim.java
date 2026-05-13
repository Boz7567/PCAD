package lab4;

import java.util.LinkedList;

public class MyQueueLim implements MyQueue{

    private final LinkedList<String> queue = new LinkedList<>();
    private static int LIM;

    public MyQueueLim(int lim){
        super();
        LIM = lim;
    }

    @Override
    public synchronized void push(String val) throws InterruptedException {

        while(queue.size() >= LIM) wait();

        queue.addLast(val);

        notifyAll();
    }

    @Override
    public synchronized String pop() throws InterruptedException {
        
        while(queue.isEmpty()) wait();

        String val = queue.removeFirst();
        
        notifyAll();

        return val;
    }
}