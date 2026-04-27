public class RWbasic {
    private int data = 0; 

    public int read() {
        return data;
    }

    public void write() {
        int tmp = data;
        try { 
            Thread.sleep(10); 
        } catch (InterruptedException e) {}
        data = tmp + 1;
    }
}
