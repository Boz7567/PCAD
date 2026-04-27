public class RWext extends RWbasic {
    private boolean isRead=true;

    @Override
    public synchronized int read(){
        int val=super.read();
        isRead=true;
        notifyAll();
        return val;
    }
    
    @Override
    public synchronized void write(){
        while(!isRead){
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        super.write();
        isRead=false;
        notifyAll();
    }  
}
