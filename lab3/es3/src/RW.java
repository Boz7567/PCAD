public class RW extends RWbasic{
    private int counter;

    public RW(){
        super();
        counter = 0;
    }

    @Override
    public synchronized int read(){
        try {
            while(counter != 0){
                wait();
            }
            counter++;
            notifyAll();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return super.read();
    }
    
    @Override
    public synchronized void write(){
        try {
            while(counter == 0){
                wait();
            }
            counter--;
            notifyAll();
            super.write();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
