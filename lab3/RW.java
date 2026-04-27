public class RW extends RWbasic {
    private int numReaders=0;
    private boolean writing = false;
    
    
    @Override
    public int read(){
        startRead();
        int val=super.read();
        endRead();
        return val;
    }
    private synchronized void startRead() {
        while (writing) {
            try { wait(); } catch (InterruptedException e) {}
        }
        numReaders++;
    }

    private synchronized void endRead() {
        numReaders--;
        if (numReaders == 0) {
            notifyAll();
        }
    }

    @Override
    public synchronized void write() {
        // Uno scrittore entra solo se non ci sono altri lettori O scrittori
        while (writing || numReaders > 0) {
            try { wait(); } catch (InterruptedException e) {}
        }
        
        writing = true;
        super.write();
        writing = false;
        
        notifyAll();
    }
}
