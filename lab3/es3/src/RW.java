public class RW extends RWbasic {
    private int readers = 0;
    private boolean writing = false;

    @Override
    public int read() {
        synchronized (this) {
            while(writing) {
                try{
                    wait(); 
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            readers++;
        }

        int result = super.read();

        synchronized (this) {
            readers--;
            if (readers == 0) {
                notifyAll();
            }
        }
        return result;
    }

    @Override
    public void write() {
        synchronized(this){
            while (readers > 0 || writing) {
                try { wait(); } catch (InterruptedException e) {}
            }
            writing = true;
        }

        super.write();

        synchronized (this) {
            writing = false;
            notifyAll();
        }
    }
}