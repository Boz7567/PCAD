public class RW extends RWbasic {
    private int readers = 0;
    private boolean writerActive = false;

    public RW() {
        super();
    }

    @Override
    public synchronized int read() {
        try {
            while (writerActive) {
                wait();
            }
            readers++;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        int value = super.read();

        synchronized (this) {
            readers--; // esco
            if (readers == 0) {
                notifyAll();
            }
        }

        return value;
    }

    @Override
    public synchronized void write() {
        try {
            while (readers > 0 || writerActive) {
                wait();
            }

            writerActive = true;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.write();

        writerActive = false;

        notifyAll();
    }
}