public class RWext extends RWbasic {
    private int readers = 0;
    private boolean writing = false;
    private boolean valueRead = true;

    @Override
    public int read() {
        synchronized(this){
            while (writing) {
                try{
                    wait(); 
                }catch(InterruptedException e){ 
                    e.printStackTrace(); 
                }
            }
            readers++;
        }

        int result = super.read();

        synchronized(this){
            readers--;
            if (!valueRead) {
                valueRead = true;
                notifyAll();
            }
            if (readers == 0) {
                notifyAll();
            }
        }
        return result;
    }

    @Override
    public void write() {
        synchronized(this){
            while(readers > 0 || writing || !valueRead) {
                try{ 
                    wait(); 
                }catch(InterruptedException e){
                    e.printStackTrace();
                }
            }
            writing = true;
        }

        super.write();

        synchronized(this){
            writing = false;
            valueRead = false;
            notifyAll();
        }
    }
}