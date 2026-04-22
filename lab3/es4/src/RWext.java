public class RWext extends RWbasic {
    private boolean available = false;
    private boolean writerActive = false;

    @Override
    public synchronized int read() {
        while (!available) {
            try { wait(); } catch (InterruptedException e) { e.printStackTrace(); }
        }
        int value = super.read();
        available = false;
        notifyAll();
        return value;
    }

    @Override
    public synchronized void write() {
        while (writerActive || available) {
            try { wait(); } catch (InterruptedException e) { e.printStackTrace(); }
        }
        writerActive = true;
        super.write();
        available = true;
        writerActive = false;
        notifyAll();
        while (available) {
            try { wait(); } catch (InterruptedException e) { e.printStackTrace(); }
        }
    }
}