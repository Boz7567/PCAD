package lab4;

public interface MyQueue {
    public void push(String val) throws InterruptedException;
    public String pop() throws InterruptedException;
}
